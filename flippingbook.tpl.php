<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <base href="/<?php print $directory ?>/lib/" />
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  <title> <?php print $title ?> </title>
  <link rel="shortcut icon"
    href="http://www.loplabbet.no/skin/frontend/default/default/favicon.ico"
    type="image/x-icon" />
  <link type="text/css" href="css/liquid-green.css" rel="stylesheet" />

  <script type="text/javascript" src="js/liquid.js"></script>
  <script type="text/javascript" src="js/swfobject.js"></script>
  <script type="text/javascript" src="js/flippingbook.js"></script>
  <script type="text/javascript">
  <!--//--><![CDATA[//><!--
    flippingBook.contents = <?php print drupal_to_js($flippingbook['contents']) ?>;
    flippingBook.pages    = <?php print drupal_to_js($flippingbook['pages']) ?>;
    var settings = <?php print drupal_to_js($flippingbook['settings']) ?>;
    for(var key in settings) {
    	flippingBook.settings[key] = settings[key];
    }
    flippingBook.settings.downloadURL = "<?php print $flippingbook['downloadURL'] ?>";
    // define custom book settings here
    <?php print $flippingbook['settings']['jsInitCode']; ?>
    flippingBook.create();
  //--><!]]>
  </script>

</head>
<body>
  <div id="fbContainer">
    <a class="altlink" href="http://www.adobe.com/shockwave/download/download.cgi?P1_Prod_Version=ShockwaveFlash">
      <div id="altmsg">Download Adobe Flash Player.</div>
    </a>
  </div>
  <div id="fbFooter">
    <div id="fbContents">
      <select id="fbContentsMenu" name="fbContentsMenu"></select>
      <span class="fbPaginationMinor">p.&nbsp;</span>
      <span id="fbCurrentPages"><?php print $current_page ?></span>
      <span id="fbTotalPages" class="fbPaginationMinor"></span>
    </div>
    <div id="fbMenu">
      <img src="img/btnZoom.gif"    width="36" height="40" border="0" id="fbZoomButton" />
      <img src="img/btnPrint.gif"    width="36" height="40" border="0" id="fbPrintButton" />
      <img src="img/btnDownload.gif" width="36" height="40" border="0" id="fbDownloadButton" />
      <img src="img/btnDiv.gif"      width="13" height="40" border="0" />
      <img src="img/btnPrevious.gif" width="36" height="40" border="0" id="fbBackButton" />
      <img src="img/btnNext.gif"     width="36" height="40" border="0" id="fbForwardButton" />
    </div>
  </div>
</body>
</html>