#!/usr/bin/env python
import rospy

import time
import actionlib
from py_fancy_action_server.msg import TimerAction, TimerGoal, TimerResult, TimerFeedback

def do_timer(goal):
  start_time = time.time()
  update_count = 0

  if goal.time_to_wait() > 60.0:
    result = TimerResult()
    result.time_elapsed = rospy.Duration.from_sec(time.time() - start_time)
    result.updates_sent = 0
    server.set_succeeded(result)

rospy.init_node('timer_action_server')
server = actionlib.SimpleActionServer('timer', TimerAction, do_timer, False)
server.start()
rospy.spin()