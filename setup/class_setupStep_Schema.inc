<?php

/*
   This code is part of GOsa (https://gosa.gonicus.de)
   Copyright (C) 2007 Fabian Hickert

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


class Step_Schema extends setup_step
{
  var $checked = array();
  var $not_checked = array();
  var $schema_readable  = FALSE;
  var $attributes       = array("enable_schema_check","samba_version");
  var $enable_schema_check = TRUE;
  var $samba_version       = 3;

  function Step_Schema()
  {
    $this->update_strings();
  }

  
  function update_strings()
  {
    $this->s_title      = _("LDAP schema check");
    $this->s_title_long = _("LDAP schema check");
    $this->s_info       = _("Perform test on your current LDAP schema");
  }

  
  function execute()
  {
    $this->check_schema();
    $failed_checks = 0 ; 
    foreach($this->checked as $val) {
      if(!$val['STATUS']){
        $failed_checks ++;
      }
    }

    if($failed_checks == 0){
      $this->is_completed = TRUE;
    }else{
      $this->is_completed = TRUE;
    }

    $smarty = get_smarty();
    $smarty->assign("bool",array(FALSE => _("No"), TRUE => _("Yes")));
    $smarty->assign("schema_readable",$this->schema_readable);
    $smarty->assign("enable_schema_check",$this->enable_schema_check);
    $smarty->assign("checks",$this->checked);
    $smarty->assign("not_checked",$this->not_checked);
    $smarty->assign("failed_checks",$failed_checks);
    return($smarty -> fetch (get_template_path("../setup/setup_schema.tpl")));
  }

  function save_object()
  {
    if(isset($_POST['step7_posted'])){

      /* Get attributes */
      foreach($this->attributes as $attr){
        if(isset($_POST[$attr])){
          $this->$attr = validate($_POST[$attr]);
        }
      }
    }
  }

  function check_schema()
  {
    $cfg = $this->parent->captured_values;
    $rfc2307bis = $cfg['rfc2307bis'];
    $this->checked = check_schema($cfg,$rfc2307bis);

    /* Get objectclasses */
    $ldap = new LDAP($cfg['admin'],$cfg['password'],$cfg['connection'] ,FALSE,$cfg['tls']);
    $objectclasses = $ldap->get_objectclasses();
    if(count($objectclasses) == 0){
      print_red(_("Can't get schema information from server. No schema check possible!"));
    }

    /* Which samba version do we use? */
    if(isset($objectclasses['sambaSamAccount'])){
      $this->samba_version = 3;
    } elseif(isset($objectclasses['sambaAccount'])) {
      $this->samba_version = 2;
    }else{
      $this->samba_version = 0;
    }
  }
}

// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>