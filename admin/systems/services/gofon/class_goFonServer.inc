<?php

class goFonServer extends goService
{

    var $cli_summary      = "This pluign is used within the ServerService Pluign \nand indicates that this server supports asterisk management.";
    var $cli_description  = "Some longer text\nfor help";
    var $cli_parameters   = array("eins" => "Eins ist toll", "zwei" => "Zwei ist noch besser");

    /* This plugin only writes its objectClass */
    var $objectclasses    = array("goFonServer");
    var $attributes       = array("goFonAdmin", "goFonPassword", "goFonAreaCode", "goFonCountryCode");
    var $StatusFlag       = "goFonServerStatus";

    /* This class can't be assigned twice so it conflicts with itsself */
    var $conflicts        = array("goFonServer");

    var $DisplayName      = "";
    var $dn               = NULL;
    var $cn               = "";
    var $acl;

    var $goFonServerStatus  = "";
    var $goFonPassword      = "";
    var $goFonAdmin         = "";
    var $goFonAreaCode      = "";
    var $goFonCountryCode   = "";
    var $view_logged  = FALSE;

    var $orig_dn            = "";

    function __construct(&$config, $dn)
    {
        goService::__construct($config, $dn);
        $this->DisplayName = _("VoIP service");

        $this->orig_dn = $dn;
    }


    function execute()
    {
        if ($this->is_account && !$this->view_logged) {
            $this->view_logged = TRUE;
            new log("view", "server/" . get_class($this), $this->dn);
        }

        $smarty = get_smarty();
        foreach ($this->attributes as $attr) {
            $smarty->assign($attr, set_post($this->$attr));
        }

        /* Assign acls */
        $tmp = $this->plInfo();
        foreach ($tmp['plProvidedAcls'] as $name => $translation) {
            $smarty->assign($name . "ACL", $this->getacl($name));
        }

        return ($smarty->fetch(get_template_path("goFonServer.tpl", TRUE, dirname(__FILE__))));
    }


    function getListEntry()
    {
        $fields = goService::getListEntry();
        $fields['Message']    = _("VoIP service") . " - " . _("Asterisk management");
        #$fields['AllowEdit']  = true;
        return ($fields);
    }

    function check()
    {
        $message = plugin::check();
        if (empty($this->goFonAdmin)) {
            $message[] = msgPool::required(_("User"));
        }
        if (empty($this->goFonPassword)) {
            $message[] = msgPool::required(_("Password"));
        }
        if (empty($this->goFonAreaCode)) {
            $message[] = msgPool::required(_("Local dial prefix"));
        }
        if (empty($this->goFonCountryCode)) {
            $message[] = msgPool::required(_("Country prefix"));
        }
        return ($message);
    }


    function save_object()
    {
        if (isset($_POST['goFonServerPosted'])) {
            plugin::save_object();
        }
    }


    function allow_remove()
    {
        /* Check if we are able to remove the asterisk database. If the database is still in use skip */
        if ($this->is_account) {
            $ldap = $this->config->get_ldap_link();
            $ldap->cd($this->config->current['BASE']);
            $ldap->search("(&(goFonHomeServer=" . $this->dn . ")(|(uid=*)(cn=*)))", array("dn", "uid", "cn", "goFonHomeServer"));
            if ($ldap->count()) {

                /* Number of entries shown in warning */
                $i    = 3;
                $str  = "";
                while (($attrs = $ldap->fetch()) && $i >= 0) {
                    $i--;
                    if (isset($attrs['uid'][0])) {
                        $str .= $attrs['uid'][0] . " ";
                    } else {
                        $str .= $attrs['cn'][0] . " ";
                    }
                }

                /* Some entries found */
                if ($i != 3) {
                    return (sprintf(_("You can't remove the asterisk database extension, it is still in use by these objects '%s'."), trim($str)));
                }
            }
        }
    }


    function save()
    {
        goService::save();
        /* Update goFonAccounts if server was is renamed.
           Set attribute goFonHomeServer to current dn
         */
        if (in_array_strict("goFonServer", $this->objectclasses)) {
            if ($this->orig_dn != "new" && $this->orig_dn != $this->dn) {
                $ldap = $this->config->get_ldap_link();
                $ldap->cd($this->config->current['BASE']);
                $ldap->search("(&(goFonHomeServer=" . $this->orig_dn . ")(|(objectClass=goFonAccount)(objectClass=goFonConference)))", array("goFonHomeServer"));
                $dns = array();
                while ($attrs = $ldap->fetch()) {
                    $dns[] = $attrs['dn'];
                }
                foreach ($dns as $dn) {
                    $ldap->cd($dn);
                    $ldap->modify(array("goFonHomeServer" => $this->dn));
                    if (!$ldap->success()) {
                        msg_dialog::display(_("LDAP error"), msgPool::ldaperror($ldap->get_error(), $dn, LDAP_MOD, __CLASS__));
                    }
                }
            }

            /* Updated config list of gofon servers */
            if ($this->orig_dn == "new" || $this->orig_dn != $this->dn) {
                $config = session::get('config');
                $config->load_servers();
                session::set('config', $config);
            }
        }
    }


    /* Return plugin informations for acl handling */
    static function plInfo()
    {
        return (array(
            "plShortName"   => _("VoIP service"),
            "plDescription" => _("VoIP - asterisk management") . " (" . _("Services") . ")",
            "plSelfModify"  => FALSE,
            "plDepends"     => array(),
            "plPriority"    => 92,
            "plSection"     => array("administration"),
            "plCategory"    => array("server"),

            "plRequirements" => array(
                'ldapSchema' => array('goFonServer' => '>=2.7'),
                'onFailureDisablePlugin' => array(__CLASS__, 'fonreport', 'goFonMacro', 'phoneAccount', 'phoneConferenceManagment')
            ),

            "plProvidedAcls" => array(
                "start"         => _("Start"),
                "stop"          => _("Stop"),
                "restart"       => _("Restart"),

                "goFonAdmin"      => _("Administrator"),
                "goFonPassword"   => _("Password"),
                "goFonAreaCode"   => _("Area code"),
                "goFonCountryCode" => _("Country code")
            )
        ));
    }
}
