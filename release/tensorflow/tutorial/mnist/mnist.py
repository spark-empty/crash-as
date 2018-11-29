#! /bin/python3

# according to https://www.tensorflow.org/get_started/mnist/beginners
# pip install --ignore-installed --upgrade tensorflow

# http://deeplearning.net/tutorial/gettingstarted.html

import os
import sys
from PIL import Image
import argparse
import time
parser = argparse.ArgumentParser()
parser.add_argument('-m', dest="model", help='specify the model name < one, two, or a *pb file >')
parser.add_argument('-d', dest="debug", action='store_true', default=False, help='enable tersorboard debugger')
parser.add_argument('-l', dest="log", action='store_true', default=False, help='log the graph')
parser.add_argument('-f', dest="freeze", action='store_true', default=False, help='freeze the graph as mnist.pb')
parser.add_argument('--ckp', dest="const_keep_prob", action='store_true', default=False, help='keep_prob set to const 1.0')

options = parser.parse_args()

# download of MNIST data
if(not os.path.exists('train-images-idx3-ubyte.gz')):
    os.system('wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz')
    os.system('wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz')
    os.system('wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz')
    os.system('wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz')

# hack of the MNIST data 
def extract_mnist_image(image, label, p, limit=1000):
    if(not os.path.exists(p)): os.mkdir(p)
    def U32(b):
        return (b[0]<<24)+(b[1]<<16)+(b[2]<<8)+(b[3]<<0)

    def RGB(b):
        if(0 == b[0]):
            return (0xFF,0xFF,0xFF)
        return (b[0],0,0)
    with gzip.open(image,'rb') as f:
        f2 = gzip.open(label,'rb')
        magic = U32(f.read(4))
        print('magic', magic)
        number = U32(f.read(4))
        print('number of images', number)
        raws = U32(f.read(4))
        print('raws', raws)
        cols = U32(f.read(4))
        print('coloumns', cols)
        magic = U32(f2.read(4))
        print('magic', magic)
        number2 = U32(f2.read(4))
        print('number of labels', number2)
        assert(number == number2)
        for i in range(number):
            img = Image.new('RGB',(raws,cols),(255,255,255))
            pixels = img.load()
            for w in range(raws):
                for h in range(cols):
                    pixels[w,h] = RGB(f.read(1))
            iname = '%s/img%d_%d.png'%(p,i,f2.read(1)[0])
            img.save(iname,'PNG')
            if(i > limit):
                print('too many images, reach the limit %d, stop!'%(limit))
                break
        f2.close()
        print('convert MNIST data to image under directory %s done!'%(p));

if(not os.path.exists('tmp')):
    import gzip
    os.mkdir('tmp')
    extract_mnist_image('train-images-idx3-ubyte.gz', 'train-labels-idx1-ubyte.gz', 'tmp/train')
    extract_mnist_image('t10k-images-idx3-ubyte.gz', 't10k-labels-idx1-ubyte.gz', 'tmp/test')

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("./", one_hot=True)

import tensorflow as tf

sess = tf.InteractiveSession()

def mnist_one_train():
    x = tf.placeholder(tf.float32, [None, 784], name='x')
    y_ = tf.placeholder(tf.float32, [None, 10], name='y_')
    W = tf.Variable(tf.zeros([784, 10]), name='W')
    b = tf.Variable(tf.zeros([10]), name='b')
    y = tf.nn.softmax(tf.matmul(x, W) + b,name='y')
    cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))
    train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)
    correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    sess.run(tf.global_variables_initializer())
    for i in range(1000):
        batch_xs, batch_ys = mnist.train.next_batch(100)
        sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
        if(i%100 == 0):
            train_accuracy = accuracy.eval(feed_dict={x:batch_xs, y_: batch_ys})
            print("step %d, training accuracy %g"%(i, train_accuracy))
    return x,y,y_

# according to http://www.tensorfly.cn/tfdoc/tutorials/mnist_pros.html
def weight_variable(shape, name):
  initial = tf.truncated_normal(shape, stddev=0.1, name=name+'_initial')
  return tf.Variable(initial, name=name)

def bias_variable(shape, name):
  initial = tf.constant(0.1, shape=shape, name=name+'_initial')
  return tf.Variable(initial, name=name)

def conv2d(x, W, name):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME', name=name)

def max_pool_2x2(x, name):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME', name=name)

def mnist_two_train():
    x = tf.placeholder(tf.float32, [None, 784], name='x')
    y_ = tf.placeholder(tf.float32, [None, 10], name='y_')
    W_conv1 = weight_variable([5, 5, 1, 32], name='W_conv1')
    b_conv1 = bias_variable([32], name='b_conv1')
    x_image = tf.reshape(x, [-1,28,28,1], name='x_image')
    h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1, name='conv2d1') + b_conv1, name='h_conv1')
    h_pool1 = max_pool_2x2(h_conv1, name='h_pool1')
    W_conv2 = weight_variable([5, 5, 32, 64], name='W_conv2')
    b_conv2 = bias_variable([64], name='b_conv2')

    h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2, name='conv2d2') + b_conv2, name='h_conv2')
    h_pool2 = max_pool_2x2(h_conv2, name='h_pool2')
    W_fc1 = weight_variable([7 * 7 * 64, 1024], name='W_fc1')
    b_fc1 = bias_variable([1024], name='b_fc1')

    h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64], name='h_pool2_flat')
    h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1, name='h_fc1')
    if(options.const_keep_prob):
        keep_prob = tf.constant(1.0, name='keep_prob')
    else:
        keep_prob = tf.placeholder(tf.float32, name='keep_prob')
    h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob, name='h_fc1_drop')
    W_fc2 = weight_variable([1024, 10], name='W_fc2')
    b_fc2 = bias_variable([10], name='b_fc2')

    y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2, name='y')
    cross_entropy = -tf.reduce_sum(y_*tf.log(y_conv))
    train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
    correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    sess.run(tf.global_variables_initializer())
    for i in range(1000):
        batch_xs, batch_ys = mnist.train.next_batch(100)
        if(options.const_keep_prob):
            train_step.run(feed_dict={x: batch_xs, y_: batch_ys})
        else:
            train_step.run(feed_dict={x: batch_xs, y_: batch_ys, keep_prob: 0.5})
        if(i%100 == 0):
            if(options.const_keep_prob):
                train_accuracy = accuracy.eval(feed_dict={x:batch_xs, y_: batch_ys})
            else:
                train_accuracy = accuracy.eval(feed_dict={x:batch_xs, y_: batch_ys, keep_prob: 1.0})
            print("step %d, training accuracy %g"%(i, train_accuracy))
    return x,y_conv,y_

def mnist_load(model):
    with tf.gfile.FastGFile(model, 'rb') as f:
        graph_def = tf.GraphDef()
        graph_def.ParseFromString(f.read())
        _ = tf.import_graph_def(graph_def, name='')
    print('Graph loaded.')
    
    x = sess.graph.get_tensor_by_name('x:0')
    y = sess.graph.get_tensor_by_name('y:0')
    y_ = tf.placeholder(tf.float32, [None, 10], name='y_')
    sess.run(tf.global_variables_initializer())
    return x,y,y_

if(options.model == 'one'):
    x,y,y_ = mnist_one_train()
    options.const_keep_prob = True
elif(options.model == 'two'):
    x,y,y_ = mnist_two_train()
else:
    x,y,y_ = mnist_load(options.model)

if(options.freeze):
    # https://zhuanlan.zhihu.com/p/32887066
    print('export frozen graph mnist.pb')
    from tensorflow.python.framework import graph_util
    #tf.train.write_graph(sess.graph_def, './', 'mnist.pb', False)
    #tf.train.Saver().save(sess, './ckpt/mnist.ckpt')
    constant_graph = graph_util.convert_variables_to_constants(sess, sess.graph_def, ['y'])
    with tf.gfile.FastGFile('./mnist.pb', mode='wb') as f:
        f.write(constant_graph.SerializeToString())

# and then uncomment below 2 lines to debug
if(options.debug):
    os.system('gnome-terminal -- tensorboard --logdir logdir --debugger_port 6064 --port=6077')
    time.sleep(3)
    os.system('firefox http://localhost:6077/')
    time.sleep(3)
    from tensorflow.python import debug as tf_debug
    sess = tf_debug.TensorBoardDebugWrapperSession(sess, 'localhost:6064')

# uncommnet out the below line of code to log out the graph to view it in tensorboard
if(options.log):
    writer = tf.summary.FileWriter('./graphs', sess.graph)
    print('export log ./graphs')
# and run : $ tensorboard --logdir="./graphs"

correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

if(not options.const_keep_prob):
    keep_prob = sess.graph.get_tensor_by_name('keep_prob:0')

# feed a limited number of pics each time for PC with small memory
tsum = len(mnist.test.images)
ftimes = 10
fnum = int(tsum/ftimes)
for i in range(ftimes):
    if(options.const_keep_prob):
        print("test %s accuracy %g"%(i, accuracy.eval(feed_dict={x: mnist.test.images[i*fnum:(i+1)*fnum], y_: mnist.test.labels[i*fnum:(i+1)*fnum]})))
    else:
        print("test %s accuracy %g"%(i,accuracy.eval(feed_dict={x: mnist.test.images[i*fnum:(i+1)*fnum], y_: mnist.test.labels[i*fnum:(i+1)*fnum], keep_prob: 1.0})))

index = 10
while(index >= 0):
    index = input('index of test image of MNIST:')
    index = int(index)
    if(index < 0): break
    os.system('ls tmp/test/img%d_*.png'%(index))
    # save the test image to png file for check
    img = Image.new('RGB',(28,28),(255,255,255))
    pixels = img.load()
    def RGB(b):
        if(0 == b):
            return (0xFF,0xFF,0xFF)
        return (int((b*255))&0xFF,0,0)
    for i,b in enumerate(mnist.test.images[index]):
        pixels[int(i/28),i%28] = RGB(b)
    img.save('test.png','PNG')
    if(options.const_keep_prob):
        a = sess.run(y, feed_dict={x: mnist.test.images[index:index+1]})
    else:
        a = sess.run(y, feed_dict={x: mnist.test.images[index:index+1], keep_prob:1.0})
    for i,p in enumerate(a[0]):
        if(p> 0.5):
            fix = 'Y'
        else:
            fix = 'N'
        print('[%d](./test.png) is %02d%% percent to be %s %s'%(index,int(p*100),i,fix))

