; Auto-generated. Do not edit!


(cl:in-package rosserial_msgs-msg)


;//! \htmlinclude myTest.msg.html

(cl:defclass <myTest> (roslisp-msg-protocol:ros-message)
  ((my_name
    :reader my_name
    :initarg :my_name
    :type cl:string
    :initform "")
   (last_name
    :reader last_name
    :initarg :last_name
    :type cl:string
    :initform "")
   (age
    :reader age
    :initarg :age
    :type cl:fixnum
    :initform 0)
   (score
    :reader score
    :initarg :score
    :type cl:integer
    :initform 0))
)

(cl:defclass myTest (<myTest>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <myTest>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'myTest)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rosserial_msgs-msg:<myTest> is deprecated: use rosserial_msgs-msg:myTest instead.")))

(cl:ensure-generic-function 'my_name-val :lambda-list '(m))
(cl:defmethod my_name-val ((m <myTest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_msgs-msg:my_name-val is deprecated.  Use rosserial_msgs-msg:my_name instead.")
  (my_name m))

(cl:ensure-generic-function 'last_name-val :lambda-list '(m))
(cl:defmethod last_name-val ((m <myTest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_msgs-msg:last_name-val is deprecated.  Use rosserial_msgs-msg:last_name instead.")
  (last_name m))

(cl:ensure-generic-function 'age-val :lambda-list '(m))
(cl:defmethod age-val ((m <myTest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_msgs-msg:age-val is deprecated.  Use rosserial_msgs-msg:age instead.")
  (age m))

(cl:ensure-generic-function 'score-val :lambda-list '(m))
(cl:defmethod score-val ((m <myTest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_msgs-msg:score-val is deprecated.  Use rosserial_msgs-msg:score instead.")
  (score m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <myTest>) ostream)
  "Serializes a message object of type '<myTest>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'my_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'my_name))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'last_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'last_name))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'score)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'score)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'score)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'score)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <myTest>) istream)
  "Deserializes a message object of type '<myTest>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'my_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'last_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'last_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'score)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'score)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'score)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'score)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<myTest>)))
  "Returns string type for a message object of type '<myTest>"
  "rosserial_msgs/myTest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'myTest)))
  "Returns string type for a message object of type 'myTest"
  "rosserial_msgs/myTest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<myTest>)))
  "Returns md5sum for a message object of type '<myTest>"
  "19b7d3627de9a4555d2aaa19dbf70a1d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'myTest)))
  "Returns md5sum for a message object of type 'myTest"
  "19b7d3627de9a4555d2aaa19dbf70a1d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<myTest>)))
  "Returns full string definition for message of type '<myTest>"
  (cl:format cl:nil "string my_name~%string last_name~%uint8 age~%uint32 score~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'myTest)))
  "Returns full string definition for message of type 'myTest"
  (cl:format cl:nil "string my_name~%string last_name~%uint8 age~%uint32 score~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <myTest>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'my_name))
     4 (cl:length (cl:slot-value msg 'last_name))
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <myTest>))
  "Converts a ROS message object to a list"
  (cl:list 'myTest
    (cl:cons ':my_name (my_name msg))
    (cl:cons ':last_name (last_name msg))
    (cl:cons ':age (age msg))
    (cl:cons ':score (score msg))
))
