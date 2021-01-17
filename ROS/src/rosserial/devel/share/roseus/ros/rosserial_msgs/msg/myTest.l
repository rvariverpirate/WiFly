;; Auto-generated. Do not edit!


(when (boundp 'rosserial_msgs::myTest)
  (if (not (find-package "ROSSERIAL_MSGS"))
    (make-package "ROSSERIAL_MSGS"))
  (shadow 'myTest (find-package "ROSSERIAL_MSGS")))
(unless (find-package "ROSSERIAL_MSGS::MYTEST")
  (make-package "ROSSERIAL_MSGS::MYTEST"))

(in-package "ROS")
;;//! \htmlinclude myTest.msg.html


(defclass rosserial_msgs::myTest
  :super ros::object
  :slots (_my_name _last_name _age _score ))

(defmethod rosserial_msgs::myTest
  (:init
   (&key
    ((:my_name __my_name) "")
    ((:last_name __last_name) "")
    ((:age __age) 0)
    ((:score __score) 0)
    )
   (send-super :init)
   (setq _my_name (string __my_name))
   (setq _last_name (string __last_name))
   (setq _age (round __age))
   (setq _score (round __score))
   self)
  (:my_name
   (&optional __my_name)
   (if __my_name (setq _my_name __my_name)) _my_name)
  (:last_name
   (&optional __last_name)
   (if __last_name (setq _last_name __last_name)) _last_name)
  (:age
   (&optional __age)
   (if __age (setq _age __age)) _age)
  (:score
   (&optional __score)
   (if __score (setq _score __score)) _score)
  (:serialization-length
   ()
   (+
    ;; string _my_name
    4 (length _my_name)
    ;; string _last_name
    4 (length _last_name)
    ;; uint8 _age
    1
    ;; uint32 _score
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _my_name
       (write-long (length _my_name) s) (princ _my_name s)
     ;; string _last_name
       (write-long (length _last_name) s) (princ _last_name s)
     ;; uint8 _age
       (write-byte _age s)
     ;; uint32 _score
       (write-long _score s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _my_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _my_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _last_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _last_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _age
     (setq _age (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _score
     (setq _score (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get rosserial_msgs::myTest :md5sum-) "19b7d3627de9a4555d2aaa19dbf70a1d")
(setf (get rosserial_msgs::myTest :datatype-) "rosserial_msgs/myTest")
(setf (get rosserial_msgs::myTest :definition-)
      "string my_name
string last_name
uint8 age
uint32 score

")



(provide :rosserial_msgs/myTest "19b7d3627de9a4555d2aaa19dbf70a1d")


