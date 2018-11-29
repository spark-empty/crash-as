#! /bin/python3

# https://github.com/tensorflow/models/blob/master/research/slim/nets/alexnet.py
import sys,os
import argparse
import tensorflow as tf
import numpy as np
import glob
import random


parser = argparse.ArgumentParser()
parser.add_argument('-m', dest='model', default='alexnet', help='specify the model name < alexnet, inception_v3, or a *pb file >')
parser.add_argument('-a', dest='ckpt', default=None, help='the pretrained checkpoint path')
parser.add_argument('-i', dest='input', default='x:0', help='the name of input tensor')
parser.add_argument('-o', dest='output', default='y:0', help='the name of output tensor')
parser.add_argument('-f', dest="freeze", action='store_true', default=False, help='freeze the graph')

parser.add_argument('-W', dest="width",  type=int, default=224, help='input image width')
parser.add_argument('-H', dest="height", type=int, default=224, help='input image height')

options = parser.parse_args()

if(not os.path.exists('./flower_photos')):
    os.system('wget http://download.tensorflow.org/example_images/flower_photos.tgz')
    os.system('tar xf flower_photos.tgz')

class_names = ['daisy', 'dandelion', 'roses', 'sunflowers', 'tulips']

class TrainingDataset():
    def __init__(self):
        self.datasets = []
        for label,cls in enumerate(class_names):
            for imgfile in glob.glob('flower_photos/%s/*.jpg'%(cls)):
                index = random.randint(0,len(self.datasets))
                self.datasets.insert(index, (imgfile,label))
        self.pos = 0
        self.sizes = len(self.datasets)
        print('dataset size is', self.sizes)

    def next_batch(self, batchsz):
        # https://blog.csdn.net/zsean/article/details/76383100
        # https://github.com/tensorflow/hub/blob/master/examples/image_retraining/retrain.py
        X = []
        Y = []
        if(batchsz > (self.sizes-self.pos)):
            batchsz = self.sizes - self.pos
        for id,(imgfile,label) in enumerate(self.datasets[self.pos:self.pos+batchsz]):
            #print('loading', id, imgfile)
            image_raw_data = tf.gfile.GFile(imgfile,'rb').read()
            img_data = tf.image.decode_jpeg(image_raw_data)
            img = tf.image.resize_images(img_data, [options.height,options.width],method=0)
            X.append(img.eval())
            y =  np.zeros(len(class_names))
            y[label] = 1.0
            Y.append(y)
        self.pos += batchsz
        if(self.pos >= self.sizes):
            self.pos = 0
            random.shuffle(self.datasets)
        return X,Y

class TrainingDataset2():
    # https://zhuanlan.zhihu.com/p/30751039
    # https://zhuanlan.zhihu.com/p/27238630
    def __init__(self):
        pass
        # TODO: how to use tf Dataset queue reader

def alexnet_slim_model():
    from tensorflow.contrib.slim import nets
    x = tf.placeholder(tf.float32, [None, options.height,options.width,3], name='x')
    y_ = tf.placeholder(tf.float32, [None, len(class_names)], name='y_')
    model,end_points= nets.alexnet.alexnet_v2(x,len(class_names))
    return x,end_points['alexnet_v2/fc8'],y_

def inception_v3_slim_model():
    from tensorflow.contrib.slim import nets
    x = tf.placeholder(tf.float32, [None, options.height,options.width,3], name='x')
    y_ = tf.placeholder(tf.float32, [None, len(class_names)], name='y_')
    model,end_points= nets.inception.inception_v3(x,len(class_names))
    if(options.ckpt is None):
        options.ckpt = 'inception_v3.ckpt'
    if(not os.path.exists(options.ckpt)):
        os.system('wget http://download.tensorflow.org/models/inception_v3_2016_08_28.tar.gz')
        os.system('tar xf inception_v3_2016_08_28.tar.gz')
    return x,end_points['Predictions'],y_

nets = {'alexnet': alexnet_slim_model,
        'inception_v3': inception_v3_slim_model }

def loadpb(model):
    with tf.gfile.FastGFile(model, 'rb') as f:
        graph_def = tf.GraphDef()
        graph_def.ParseFromString(f.read())
        _ = tf.import_graph_def(graph_def, name='')
    print('Graph loaded.')

    x = sess.graph.get_tensor_by_name(options.input)
    y = sess.graph.get_tensor_by_name(options.output)
    y_ = tf.placeholder(tf.float32, [None, len(class_names)], name='y_')
    sess.run(tf.global_variables_initializer())
    return x,y,y_

def train(x, y, y_):
    datasets = TrainingDataset()
    cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))
    train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)
    correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    sess.run(tf.global_variables_initializer())
    checkpoint_dir  = './ckpt_'+options.model
    ckpt = tf.train.get_checkpoint_state(checkpoint_dir)
    saver=tf.train.Saver(max_to_keep=5)
    if(ckpt and ckpt.model_checkpoint_path): 
        saver.restore(sess, ckpt.model_checkpoint_path)
        print('restore checkpoint from', ckpt.model_checkpoint_path)
    elif(options.ckpt and os.path.exists(options.ckpt)):
        print('restore checkpoint from', options.ckpt)
        # https://github.com/tensorflow/tensorflow/issues/312
        reader = tf.train.NewCheckpointReader(options.ckpt)
        saved_shapes = reader.get_variable_to_shape_map()
        var_names = sorted([(var.name, var.name.split(':')[0]) for var in tf.global_variables()
                if var.name.split(':')[0] in saved_shapes])
        restore_vars = []
        with tf.variable_scope('', reuse=True):
            for var_name, saved_var_name in var_names:
                curr_var = tf.get_variable(saved_var_name)
                var_shape = curr_var.get_shape().as_list()
                if var_shape == saved_shapes[saved_var_name]:
                    restore_vars.append(curr_var)
        saver2=tf.train.Saver(restore_vars)
        saver2.restore(sess, options.ckpt)
    for i in range(10000):
        batch_xs, batch_ys = datasets.next_batch(100)
        sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
        if(i%100 == 0):
            train_accuracy = accuracy.eval(feed_dict={x:batch_xs, y_: batch_ys})
            print("step %d, training accuracy %g"%(i, train_accuracy))
            saver.save(sess, checkpoint_dir + '/model.ckpt', global_step=i+1)  
    return x,y,y_

sess = tf.InteractiveSession()

try:
    x,y,y_ = nets[options.model]()
except KeyError:
    x,y,y_ = loadpb(options.model)

train(x,y,y_)

if(options.freeze):
    print('export frozen graph %s.pb',options.model)
    from tensorflow.python.framework import graph_util
    constant_graph = graph_util.convert_variables_to_constants(sess, sess.graph_def, ['y'])
    with tf.gfile.FastGFile('./%s.pb'%(options.model), mode='wb') as f:
        f.write(constant_graph.SerializeToString())

