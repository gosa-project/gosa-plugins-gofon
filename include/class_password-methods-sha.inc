<?php
/*
   This code is part of GOsa (https://gosa.gonicus.de)
   Copyright (C) 2004  Fabian Hickert 

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

class passwordMethodsha extends passwordMethod
{
  function passwordMethodsha($config)  
  {
  }

  function is_available()
  {
    if (function_exists('sha1')){
      return(true);
    }elseif(function_exists('mhash')){
      return true;
    }elseif(function_exists('crypt')){
      return true;
    }else{
      return false;
    }
  }


  function generate_hash($password)
  {
    if (function_exists('sha1')) {
      $hash = "{SHA}" . base64_encode(pack("H*",sha1($password)));
    }elseif (function_exists('mhash')) {
      $hash = "{SHA}" . base64_encode(mHash(MHASH_SHA1, $password));
    }elseif(function_exists('crypt')) {
      $hash = "{CRYPT}" . crypt($password);
    }else{
      print_red(_("Can't use sha for encryption, missing function sha1 / mhash / crypt"));
      return false;
    }

    return $hash; 
  }
}

// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>