
(cl:in-package :asdf)

(defsystem "rosserial_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Log" :depends-on ("_package_Log"))
    (:file "_package_Log" :depends-on ("_package"))
    (:file "RPY" :depends-on ("_package_RPY"))
    (:file "_package_RPY" :depends-on ("_package"))
    (:file "TopicInfo" :depends-on ("_package_TopicInfo"))
    (:file "_package_TopicInfo" :depends-on ("_package"))
    (:file "myTest" :depends-on ("_package_myTest"))
    (:file "_package_myTest" :depends-on ("_package"))
  ))