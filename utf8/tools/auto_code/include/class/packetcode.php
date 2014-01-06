<?php
/*
 * auto_code just use for pap.
 * @link https://github.com/viticm/pap
 * @package auto code
 */

/**
 * Description of PacketCode
 * about packet all code auto create class(project muse be include base.php)
 * @author viticm<viticm@126.com>
 * @version 1.0
 */
 class PacketCode {
   
   private $formatcode_;
   
   /**
    * construct function
    * @param void
    * @return void
    */
   public function __construct() {
     $this->formatcode_ = NULL;
   }
   
   /**
    * get format code, replace all note code
    * @param string $code
    * @return void
    */
   public function get_formatcode($code = NULL) {
     if (NULL == $code) return;
     $codestr = str_replace("\r", '', $this->repalcenote($code));
     $this->formatcode_ = $this->get_formatarray($codestr);
     /**
     $this->formatcode_ = 
       preg_replace("/(\n)\\1+/","\\1", $this->formatcode_);
     $this->formatcode_ =
       preg_replace("/^\n/","", $this->formatcode_);
     echo $this->formatcode_;
     **/ //不用去掉空行，在代码中处理即可
   }
   
   /**
    * 获取生成代码数组
    * @param string $str
    * @return array:
    */
   private function get_formatarray($str = NULL) {
     $reslut = array();
     $reslut = array(
       'modeltype' => NULL,
       'modelname' => NULL,
       'packetname' => NULL,
       'filename' => NULL,
       'include_definefile' => NULL,
       'values' => array(),
     );
     if (NULL == $str) return $reslut;
     $temp = array();
     $temp = explode(LF, $str);
     foreach ($temp as $line) {
       if (strlen(trim($line)) != 0) {
         $linearray = explode(' ', trim($line));
         $arraycount = count($linearray);
         if (2 == $arraycount) {
           list($param0, $param1) = $linearray;
         }
         elseif (4 == $arraycount) {
           list($param0, $param1, $param2, $param3) = $linearray;
         }
         if ('ModelType:' == $param0) {
           $reslut['modeltype'] = $param1;
         }
         elseif ('ModelName:' == $param0) {
           $reslut['modelname'] = $param1;
         }
         elseif ('PacketName:' == $param0) {
           $reslut['packetname'] = $param1;
         }
         elseif ('IncludeDefineFile:' == $param0) {
           $reslut['include_definefile'] = $param1;
         }
         elseif ('FileName:' == $param0) {
           $reslut['filename'] = $param1;
         }
         elseif(4 == $arraycount) {
           $value = array();
           $value['name'] = substr($param0, 1, strlen($param0) - 2);
           $value['type'] = substr($param1, 1, strlen($param1) - 2);
           $value['length'] = substr($param2, 1, strlen($param2) - 2);
           $value['note'] = substr($param3, 1, strlen($param3) - 2);
           array_push($reslut['values'], $value);
         }
       }
     }
     return $reslut;
   }
   
   /**
    * 从字符串中获取最后的命名空间以及父命名空间
    * @param string $str
    * @return bool | array
    */
   private function get_namespaceinfo($str = NULL) {
     if (NULL == $str) return false;
     $lastpos = strrpos($str, '::');
     if (false === $lastpos) return false;
     $fathernamespace = substr($str, 0, $lastpos);
     $lastvalue = 
       substr($str, $lastpos + 2, strlen($str) - ($lastpos + 2));
     $lastpos = strrpos($fathernamespace, '::');
     if (false === $lastpos) {
       $lastnamespace = $fathernamespace;
       $fathernamespace = '';
     }
     else {
       $fathernamespace_temp = $fathernamespace;
       $fathernamespace = substr($fathernamespace, 0, $lastpos);
       $lastnamespace = substr($fathernamespace_temp, 
                               $lastpos + 2, 
                               strlen($fathernamespace_temp) - ($lastpos + 2));
     }
     $result = array($fathernamespace, $lastnamespace, $lastvalue);
     return $result;
   }
   
   /**
    * @param string $str
    * @return mixed
    */
   private function repalcenote($str){
     $pos0 = strpos($str, '/*');
     while($pos0 !== false){
       $pos1 = strpos($str, '*/');
       if(false === $pos1){
         $pos0+=2;
       }else{
         $rp = substr($str, $pos0, $pos1 - $pos0 + 2);
         $str = str_replace($rp, '', $str);
         $pos0 = strpos($str, '/*');
       }
     }
     return $str;
   }
   
   /**
    * create header file
    * @param string $directory
    * @return bool
    */
   private function createheader($directory = '') {
     if (!is_array($this->formatcode_)) return false;
     $modeltype = $this->formatcode_['modeltype'];
     $modelname = $this->formatcode_['modelname'];
     $packetname = $this->formatcode_['packetname'];
     $filename = $this->formatcode_['filename'];
     $values = $this->formatcode_['values'];
     
     if (NULL == $filename) return false;
     //header model define
     $hmd = 'SERVER' == strtoupper($modeltype) ? '_SERVER' : '';
     $namespace_model = strtolower($hmd);
     $hmnd = '_'.strtoupper($modelname); //header model name define
     $hfd = '_'.strtoupper($filename); //head file name define
     $datestring = date('Y-m-d H:i:s');
     $include_definefile = $this->formatcode_['include_definefile'];
     $public_definefunctions = '';
     $private_definevariables = '';
     $include_filemodel = 'SERVER' == strtoupper($modeltype) ? 'server/' : '';
     $include_definefiles = '';
     $namespaceconnetion = '';
     $usepacket_namespace = 
       'SERVER' == strtoupper($modeltype) ? 'pap_common_net::' : '';
     $u_nc = ''; //$use_namespaceconnetion
     if (strtoupper($modeltype) != 'SERVER') {
       $u_nc = 'pap_server_common_net::';
       $namespaceconnetion = <<<EOF
namespace pap_server_common_net {

class Connection;

}; //namespace pap_server_common_net
EOF;
     }
     
     if (0 == $include_definefile) {
       $include_definefiles = '';
     }
     elseif (1 == $include_definefile) {
       $include_definefiles .= '#include "common/game/define/all.h"'.LF;
       $include_definefiles .= 
         '#include "server/common/game/define/all.h"'.LF;
     }
     elseif (2 == $include_definefile) {
       $include_definefiles .= 
         '#include "server/common/game/define/all.h"'.LF;
     }
     elseif (3 == $include_definefile) {
       $include_definefiles .= '#include "common/game/define/all.h"'.LF;
     }
     
     foreach ($values as $value) {
       $variable = $value['name'];
       $type = $value['type'];
       $length = $value['length'];
       $note = $value['note'];
       $variablename = $variable.'_';
       $gsetname = '_'.$variable;
       $lengtharray = explode(',', $length);
       $lengtharray_length = count($lengtharray);
       if ('char' == $type && $length !== '0') {
         if ($lengtharray_length == 2) {
         $public_definefunctions .=
           '   void get'.$gsetname
           .'(uint16_t index, char* buffer, uint16_t length);'.LF;
         $public_definefunctions .=
           '   void set'
           .$gsetname.'(uint16_t index, const char* '.$variable.');';
         }
         elseif (1 == $lengtharray_length) {
           $public_definefunctions .=
             '   void get'.$gsetname.'(char* buffer, uint16_t length);'.LF;
           $public_definefunctions .=
             '   void set'.$gsetname.'(const char* '.$variable.');';
         }
       }
       else {
         if($length !== '0' && 1 == $lengtharray_length) {
           $public_definefunctions .=
             '   '.$type.' get'.$gsetname.'(uint16_t index);'.LF;
           $public_definefunctions .=
             '   void set'.$gsetname
             .'(uint16_t index, '.$type.' '.$variable.');';
         }
         else {
           $public_definefunctions .=
             '   '.$type.' get'.$gsetname.'();'.LF;
           $public_definefunctions .=
             '   void set'.$gsetname.'('.$type.' '.$variable.');';
         }
       }
       $public_definefunctions .= LF;
       if ($length !== '0') {
         if ('char' == $type) $lengtharray[$lengtharray_length - 1] .= ' + 1';
         $private_definevariables .=
           '   '.$type.' '.$variablename.'['
           .implode('][', $lengtharray).']; '.'//'.$note;
       }
       else {
         $private_definevariables .= 
           '   '.$type.' '.$variablename.'; //'.$note;
       }
       $private_definevariables .= LF;
     }
     $headerinfo = <<<EOF
/**
 * PAP Engine ( https://github.com/viticm/pap )
 * \$Id {$filename}.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date {$datestring}
 * @uses packet {$packetname} class
 */
#ifndef PAP{$hmd}_COMMON_NET_PACKETS{$hmnd}{$hfd}_H_
#define PAP{$hmd}_COMMON_NET_PACKETS{$hmnd}{$hfd}_H_

#include "{$include_filemodel}common/net/config.h"
#include "{$include_filemodel}common/net/connection.h"
#include "common/net/packet.h"
#include "common/net/packetfactory.h"
{$include_definefiles}
{$namespaceconnetion}
namespace pap{$namespace_model}_common_net {

namespace packets {

class {$packetname} : public {$usepacket_namespace}Packet {

 public:
   {$packetname}();
   virtual ~{$packetname}() {};

 public:  
   virtual bool read({$usepacket_namespace}SocketInputStream& inputstream);
   virtual bool write({$usepacket_namespace}SocketOutputStream& outputstream) const;
   virtual uint32_t execute(Connection* connection);
   virtual uint16_t get_packetid() const;
   virtual uint32_t get_packetsize() const;
   
 public: 
{$public_definefunctions}
 private:
{$private_definevariables}
};

class {$packetname}Factory : public {$usepacket_namespace}PacketFactory {

 public:
   {$usepacket_namespace}Packet* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class {$packetname}Handler {

 public:
   static uint32_t execute({$packetname}* packet, {$u_nc}Connection* connection);

};

}; //namespace packets

}; //namespace pap{$namespace_model}_common_net

#endif //PAP{$hmd}_COMMON_NET_PACKETS{$hmnd}{$hfd}_H_
EOF;
     if (false === file_put_contents($directory.$filename.'.h', $headerinfo))
       return false;
     return true;
   }
   
   /**
    * create source file
    * @param string $directory
    * @return bool
    */
   private function createsource($directory = '') {
     if (!is_array($this->formatcode_)) return false;
     $modeltype = $this->formatcode_['modeltype'];
     $modelname = $this->formatcode_['modelname'];
     $packetname = $this->formatcode_['packetname'];
     $filename = $this->formatcode_['filename'];
     $values = $this->formatcode_['values'];
     
     if (NULL == $filename) return false;
     $twospace = '  ';
     $fourspace = $twospace.$twospace;
     $upper_packetname = strtoupper($packetname);
     $upper_filename = strtoupper($filename);
     $include_definefile = $this->formatcode_['include_definefile'];
     $public_definefunctions = '';
     $private_definevariables = '';
     $include_filemodel = 'SERVER' == strtoupper($modeltype) ? 'server/' : '';
     $namespacemodel = 'SERVER' == strtoupper($modeltype) ? '_server' : '';
     $include_definefiles = '';
     $include_namespaceconnetion = '';
     $usepacket_namespace =
       'SERVER' == strtoupper($modeltype) ? 'pap_common_net::' : '';
     $u_nc = ''; //$use_namespaceconnetion
     if (strtoupper($modeltype) != 'SERVER') {
       $u_nc = 'pap_server_common_net::';
       $include_namespaceconnetion = 
         '#include "server/common/net/connection.h"';
     }
     $sourcecode = '';
     $constructcode = '';
     $constructcode .= $packetname.'::'.$packetname.'() {'.LF;
     $constructcode .= $twospace.'__ENTER_FUNCTION'.LF;
     $readcode = '';
     $readcode .= 'bool '.$packetname
       .'::read('.$usepacket_namespace.'SocketInputStream& inputstream) {'.LF;
     $readcode .= $twospace.'__ENTER_FUNCTION'.LF;
     $writecode = '';
     $writecode .= 'bool '.$packetname
       .'::write('.$usepacket_namespace.'SocketOutputStream& outputstream) {'.LF;
     $writecode .= $twospace.'__ENTER_FUNCTION'.LF;
     /* get_pakcetsize and get_packet_maxsize{ */
     $sizecode = '';
     $maxsize_code = '';
     $sizecode_head = 'uint32_t '.$packetname.'::get_packetsize() const {'.LF;
     $sizecode_body = $twospace.'uint32_t result = ';
     $sizecode_end = $twospace.'return result;'.LF;
     $sizecode_end .= '}'.LF;
     $maxsize_codehead = 'uint32_t '.$packetname
                         .'Factory::get_packet_maxsize() const {'.LF;
     $maxsize_codebody = $twospace.'uint32_t result = ';
     $maxsize_codeend = $twospace.'return result;'.LF;
     $maxsize_codeend .= '}'.LF;
     $valuescount = count($values);
     
     $space18 = '                  ';
     
     $i = 0;
     /* get_pakcetsize and get_packet_maxsize} */
     foreach ($values as $value) {
       ++$i;
       $variable = $value['name'];
       $type = $value['type'];
       $length = $value['length'];
       $note = $value['note'];
       $variablename = $variable.'_';
       $gsetname = '_'.$variable;
       $lengtharray = explode(',', $length);
       $lengtharray_length = count($lengtharray);
       $lengthnamespace = array();
       if ($lengtharray_length > 1) 
         $lengthnamespace = $this->get_namespaceinfo($lengtharray[0]);
       $length_fathernamespace = '';
       $length_lastnamespace = '';
       $length_lastvalue = '';
       $length_usenamespace = '';
       $lengtharray_size = $lengtharray[0];
       if (is_array($lengthnamespace) && count($lengthnamespace) > 0) {
         list($length_fathernamespace, $length_lastnamespace,$length_lastvalue) 
           = $lengthnamespace;
         $length_usenamespace = $length_fathernamespace != '' ? 
                                'using '.$length_fathernamespace : '';
         $lengtharray_size = $length_lastnamespace.'::'.$length_lastvalue;
       }
       
       //max size code
       $maxsize_codebody .= 1 == $i ? '' : $space18.$twospace;
       $maxsize_codebody .= 'sizeof('.$variablename.')';
       $maxsize_codebody .= $valuescount != $i ? ' +'.LF : ');'.LF;
       
       if ('char' == $type && $length !== '0') {
         if ($lengtharray_length == 2) {
           
           //size code
           $sizecode_body .= 1 == $i ? '' : $space18.$twospace;
           $sizecode_body .= 'sizeof('.$variablename.') - ';
           $sizecode_body .= $lengtharray_size.' * 1';
           $sizecode_body .= $valuescount != $i ? ' +'.LF : ');'.LF;
           
           $sourcecode .=
             'void '.$packetname.'::get'.$gsetname
             .'(uint16_t index, char* buffer, uint16_t length) {'.LF;
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           if ($length_usenamespace != '') {
             $sourcecode .= $twospace.$length_usenamespace.';'.LF;
             $sizecode_body = $twospace.$length_usenamespace.';'
                              .LF.$sizecode_body;
           }
           $sourcecode .= $twospace.'if (index < 0 || index >= '
                          .$lengtharray_size.')'.LF;
           $sourcecode .= $fourspace.'return;'.LF;
           $sourcecode .= $fourspace.'snprintf(buffer, length, '
                          .variablename.'[index]);'.LF;
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
           
           $sourcecode .=
             'void '.$packetname.'::set'
             .$gsetname.'(uint16_t index, const char* value) {';
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           if ($length_usenamespace != '') {
             $sourcecode .= $fourspace.$length_usenamespace.';'.LF;
           }
           $sourcecode .= $twospace.'if (index < 0 || index >= '
                          .$lengtharray_size.')'.LF;
           $sourcecode .= $fourspace.'return;'.LF;
           $sourcecode .= $fourspace.'strncpy('.$variablename
                          .'[index], value, sizeof('
                          .$variablename.'[index]) - 1);'.LF;
           $sourcecode .= $fourspace.$variablename.'[sizeof('
                          .$variablename.'[index])] = 0;'.LF;
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
         }
         elseif (1 == $lengtharray_length) {
           
           
           //size code
           $sizecode_body .= 1 == $i ? '' : $space18.$twospace;
           $sizecode_body .= 'sizeof('.$variablename.') - 1';
           $sizecode_body .= $valuescount != $i ? ' +'.LF : ');'.LF;
           
           $sourcecode .= 'void '.$packetname.'::get'.$gsetname
                          .'(char* buffer, uint16_t length) {'.LF;
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           $sourcecode .= $fourspace.'snprintf(buffer, length, '
                          .$variablename.');'.LF;
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
           
           $sourcecode .= 'void '.$packetname.'::set'
                          .$gsetname.'(const char* '.$variable.') {'.LF;
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           $sourcecode .= $fourspace.'strncpy('.$variablename.', '.$variable
                          .', sizeof('.$variablename.') - 1);'.LF;
           $sourcecode .= $fourspace.$variablename.'[sizeof('
                          .$variablename.')] = 0;'.LF;
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
         }
       }
       else {
         //size code
         $sizecode_body .= 1 == $i ? '' : $space18.$twospace;
         $sizecode_body .= 'sizeof('.$variablename.')';
         $sizecode_body .= $valuescount != $i ? ' +'.LF : ');'.LF;
    
         if($length !== '0' && 1 == $lengtharray_length) {
           $sourcecode .=
             '   '.$type.' get'.$gsetname.'(uint16_t index) {'.LF;
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           if ($length_usenamespace != '') {
             $sourcecode .= $fourspace.$length_usenamespace.';'.LF;
           }
           $sourcecode .= $twospace.'if (index < 0 || index >= '
                          .$lengtharray_size.')'.LF;
           $sourcecode .= $fourspace.'return;'.LF;
           $sourcecode .= $fourspace.'retun '.$variablename.'[index];'.LF;
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
           
           $sourcecode .= 'void '.$packetname.'::set'.$gsetname
                          .'(uint16_t index, '.$type.' value) {'.LF;
           $sourcecode .= $twospace.'__ENTER_FUNCTION'.LF;
           $sourcecode .= $twospace.'if (index < 0 || index >= '
                          .$lengtharray_size.')'.LF;
           $sourcecode .= $fourspace.'return;'.LF;
           $sourcecode .= $fourspace.$variablename.'[index] = value;'.LF;         
           $sourcecode .= $twospace.'__LEAVE_FUNCTION'.LF;
           $sourcecode .= '}'.LF;
         }
         else {
           $sourcecode .= $type.' '.$packetname.'::get'.$gsetname.'() {'.LF;
           $sourcecode .= $twospace.'return '.$variablename.';'.LF;
           $sourcecode .= '}'.LF;
           
           $sourcecode .= 'void '.$packetname.'::set'.$gsetname
                          .'('.$type.' '.$variable.') {'.LF;
           $sourcecode .= $twospace.$variablename.' = '.$variable.LF;
           $sourcecode .= '}'.LF;
         }
       }
       if ($length !== '0') {
         if ($length_usenamespace != '') {
           $constructcode = $fourspace.$length_usenamespace.';'.LF;
         }
         if (1 == $lengtharray_length) {
           $constructcode .= $fourspace.'memset('.$variablename.', 0, '
                             .'sizeof('.$variablename.');'.LF;
         }
         elseif (2 == $lengtharray_length) {
           $constructcode .= $fourspace.'for (uint8_t i = 0; i < '
                             .$lengtharray_size.'; ++i) {'.LF;
           $constructcode .= $twospace.$fourspace.'memset('.$variablename
                             .'[i], 0, sizeof('.$variablename.'[i]);'.LF;
           $constructcode .= $fourspace.'}'.LF;
         }
       }
       
       //read and write code
       if ('char' == $type) {
         if ($length !== '0') {
           if (1 == $lengtharray_length) {
             $readcode .= $fourspace.'inputstream.read('.$variablename
                          .', sizeof('.$variablename.') - 1);'.LF;
             $writecode .= $fourspace.'outputstream.write('.$variablename
                           .', sizeof('.$variablename.') - 1);'.LF;
           }
           elseif (2 == $length) {
             if ($length_usenamespace != '') 
               $readcode .= $fourspace.$length_usenamespace.';'.LF;
               $readcode .= $fourspace.'for (uint8_t i = 0; i < '
                            .$lengtharray_size.'; ++i) {'.LF;
               $readcode .= $twospace.$fourspace.'inputstream.read('
                            .$variablename.'[i], sizeof('
                            .$variablename.'[i]) - 1);';
               $readcode .= $fourspace.'}'.LF;
               $writecode .= $fourspace.$length_usenamespace.';'.LF;
               $writecode .= $fourspace.'for (uint8_t i = 0; i < '
                             .$lengtharray_size.'; ++i) {'.LF;
               $writecode .= $twospace.$fourspace.'outputstream.write('
                             .$variablename.'[i], sizeof('
                             .$variablename.'[i]) - 1);';
               $writecode .= $fourspace.'}'.LF;
           }
         }
         else {
           $readcode .= $fourspace.'inputstream.read('.$variablename
                        .', sizeof('.$variablename.') - 1);'.LF;
           $writecode .= $fourspace.'outputstream.write('.$variablename
                         .', sizeof('.$variablename.') - 1);'.LF;
         }
       }
       else {
         if ($length != '0') {
           if (1 == $lengtharray_length) {
             $readcode .= $fourspace.$length_usenamespace.';'.LF;
             $readcode .= $fourspace.'for (uint8_t i = 0; i < '
                          .$lengtharray_size.'; ++i) {'.LF;
             $readcode .= $twospace.$fourspace
                          .'inputstream.read(static_cast<char*>(&'
                          .$variablename.'[i]), sizeof('
                          .$variablename.'[i]) - 1);';
             $readcode .= $fourspace.'}'.LF;
             $writecode .= $fourspace.$length_usenamespace.';'.LF;
             $writecode .= $fourspace.'for (uint8_t i = 0; i < '
                           .$lengtharray_size.'; ++i) {'.LF;
             $writecode .= $twospace.$fourspace
                           .'outputstream.write(static_cast<char*>(&'
                           .$variablename.'[i]), sizeof('
                           .$variablename.'[i]) - 1);';
             $writecode .= $fourspace.'}'.LF;
           }
         }
         else {
           $readcode .= $fourspace.'inputstream.read(static_cast<char*>(&'
                        .$variablename.')'
                        .', sizeof('.$variablename.'));'.LF;
           $writecode .= $fourspace.'outputstream.write(static_cast<char*>(&'
                         .$variablename.')'
                         .', sizeof('.$variablename.'));'.LF;
         }
       }
     }
     $constructcode .= $twospace.'__LEAVE_FUNCTION'.LF;
     $constructcode .= '}'.LF;
     
     $readcode .= $twospace.'__LEAVE_FUNCTION'.LF;
     $readcode .= '}'.LF;
     
     $writecode .= $twospace.'__LEAVE_FUNCTION'.LF;
     $writecode .= '}'.LF;
     
     $sizecode .= $sizecode_head.$sizecode_body.$sizecode_end;
     $maxsize_code .= $maxsize_codehead.$maxsize_codebody.$maxsize_codeend;
     
     $sourceinfo = <<<EOF
#include "{$include_filemodel}common/net/packets/{$modelname}/{$filename}.h"
{$include_namespaceconnetion}
namespace pap{$namespacemodel}_common_net {

namespace packets {
{$constructcode}
{$readcode}
{$writecode}
uint32_t {$packetname}::execute(Connection* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = {$packetname}Handler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t {$packetname}::get_packetid() const {
  using namespace pap{$namespacemodel}_common_game::define::id::packet;
  return {$modelname}::k{$packetname};
}

{$sizecode}
{$sourcecode}
{$usepacket_namespace}Packet* AskAuthFactory::createpacket() {
  __ENTER_FUNCTION
    return new {$packetname}();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t {$packetname}Factory::get_packetid() const {
  using namespace pap{$namespacemodel}_common_game::define::id::packet;
  return {$modelname}::k{$packetname};
}

{$maxsize_code}
} //namespace packets

} //namespace pap{$namespacemodel}_common_net
EOF;
     if (false === file_put_contents($directory.$filename.'.cc', $sourceinfo))
       return false;
     return true;
   }
   
   /**
    * create code file
    * @param string $directory
    * @return bool
    */
   public function create_codefile($directory = '') {
     $this->createheader($directory);
     $this->createsource($directory);
   }
   
 }