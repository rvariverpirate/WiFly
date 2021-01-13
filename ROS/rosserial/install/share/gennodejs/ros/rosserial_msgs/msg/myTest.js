// Auto-generated. Do not edit!

// (in-package rosserial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class myTest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.my_name = null;
      this.last_name = null;
      this.age = null;
      this.score = null;
    }
    else {
      if (initObj.hasOwnProperty('my_name')) {
        this.my_name = initObj.my_name
      }
      else {
        this.my_name = '';
      }
      if (initObj.hasOwnProperty('last_name')) {
        this.last_name = initObj.last_name
      }
      else {
        this.last_name = '';
      }
      if (initObj.hasOwnProperty('age')) {
        this.age = initObj.age
      }
      else {
        this.age = 0;
      }
      if (initObj.hasOwnProperty('score')) {
        this.score = initObj.score
      }
      else {
        this.score = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type myTest
    // Serialize message field [my_name]
    bufferOffset = _serializer.string(obj.my_name, buffer, bufferOffset);
    // Serialize message field [last_name]
    bufferOffset = _serializer.string(obj.last_name, buffer, bufferOffset);
    // Serialize message field [age]
    bufferOffset = _serializer.uint8(obj.age, buffer, bufferOffset);
    // Serialize message field [score]
    bufferOffset = _serializer.uint32(obj.score, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type myTest
    let len;
    let data = new myTest(null);
    // Deserialize message field [my_name]
    data.my_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [last_name]
    data.last_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [age]
    data.age = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [score]
    data.score = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.my_name.length;
    length += object.last_name.length;
    return length + 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rosserial_msgs/myTest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '19b7d3627de9a4555d2aaa19dbf70a1d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string my_name
    string last_name
    uint8 age
    uint32 score
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new myTest(null);
    if (msg.my_name !== undefined) {
      resolved.my_name = msg.my_name;
    }
    else {
      resolved.my_name = ''
    }

    if (msg.last_name !== undefined) {
      resolved.last_name = msg.last_name;
    }
    else {
      resolved.last_name = ''
    }

    if (msg.age !== undefined) {
      resolved.age = msg.age;
    }
    else {
      resolved.age = 0
    }

    if (msg.score !== undefined) {
      resolved.score = msg.score;
    }
    else {
      resolved.score = 0
    }

    return resolved;
    }
};

module.exports = myTest;
