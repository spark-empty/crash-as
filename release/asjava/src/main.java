/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
import java.util.Timer;
import java.util.TimerTask;

class Father {
	public Father() {
		System.out.println("Constructor of Father!");
	}

	public String home() {
		return "Zhongxiang, China";
	}

	public String firstName() {
		return "Wang";
	}

	public String lastName() {
		return "Shigui";
	}

	public String sex() {
		return "male";
	}

	public String fullName() {
		return firstName() + " " + lastName();
	}
}

class Son extends Father {
	private String last_name;

	public Son(String last_name) {
		System.out.println("Constructor of Son!");
		this.last_name = last_name;
	}

	public String lastName() {
		return last_name;
	}
}

class Daughter extends Son {

	public Daughter(String last_name) {
		super(last_name);
		System.out.println("Constructor of Daughter!");
	}

	public String sex() {
		return "female";
	}
}

class TimerEvent extends TimerTask {
	private int counter = 0;

	public TimerEvent() {
		System.out.println("Constructor of TimerEvent!");
	}

	private void onTimerEvent() {
		counter ++;
		System.out.println(counter);
	}

	@Override
	public void run() {
		onTimerEvent();
	}
}

public class main {

	private static Timer timer;
	
	private static void startTimer() {
		timer = new Timer();	//creates a new timer to schedule
		timer.schedule(new TimerEvent(), 400, 400);
	}

	public static void main(String[] argv) {
		Father boy,girl;
		
		System.out.println("Hello World!");
		
		boy = new Son("Fan");
		
		System.out.println(boy.fullName() + " is born at " + boy.home() + " , is " + boy.sex());
		
		girl = new Daughter("Fake");
		System.out.println(girl.fullName() + " is born at " + girl.home() + " , is " + girl.sex());
		
		startTimer();
	}
}

