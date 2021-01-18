#ifndef _ROS_rosserial_msgs_myTest_h
#define _ROS_rosserial_msgs_myTest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_msgs
{

  class myTest : public ros::Msg
  {
    public:
      typedef const char* _my_name_type;
      _my_name_type my_name;
      typedef const char* _last_name_type;
      _last_name_type last_name;
      typedef uint8_t _age_type;
      _age_type age;
      typedef uint32_t _score_type;
      _score_type score;

    myTest():
      my_name(""),
      last_name(""),
      age(0),
      score(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_my_name = strlen(this->my_name);
      varToArr(outbuffer + offset, length_my_name);
      offset += 4;
      memcpy(outbuffer + offset, this->my_name, length_my_name);
      offset += length_my_name;
      uint32_t length_last_name = strlen(this->last_name);
      varToArr(outbuffer + offset, length_last_name);
      offset += 4;
      memcpy(outbuffer + offset, this->last_name, length_last_name);
      offset += length_last_name;
      *(outbuffer + offset + 0) = (this->age >> (8 * 0)) & 0xFF;
      offset += sizeof(this->age);
      *(outbuffer + offset + 0) = (this->score >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->score >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->score >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->score >> (8 * 3)) & 0xFF;
      offset += sizeof(this->score);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_my_name;
      arrToVar(length_my_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_my_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_my_name-1]=0;
      this->my_name = (char *)(inbuffer + offset-1);
      offset += length_my_name;
      uint32_t length_last_name;
      arrToVar(length_last_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_last_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_last_name-1]=0;
      this->last_name = (char *)(inbuffer + offset-1);
      offset += length_last_name;
      this->age =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->age);
      this->score =  ((uint32_t) (*(inbuffer + offset)));
      this->score |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->score |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->score |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->score);
     return offset;
    }

    const char * getType(){ return "rosserial_msgs/myTest"; };
    const char * getMD5(){ return "19b7d3627de9a4555d2aaa19dbf70a1d"; };

  };

}
#endif
