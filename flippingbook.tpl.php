  <script type="text/javascript">
  <!--//--><![CDATA[//><!--
    flippingBook.contents = <?php print drupal_to_js($flippingbook['contents']) ?>;
    flippingBook.pages    = <?php print drupal_to_js($flippingbook['pages']) ?>;
    var settings = <?php print drupal_to_js($flippingbook['settings']) ?>;
    var colorSettingRe = /Color$/;
    for(var key in settings) {
    	flippingBook.settings[key] = settings[key];

      if (colorSettingRe.test(key)) {
    	  flippingBook.settings[key] = parseInt(flippingBook.settings[key].toString().slice(1), 16);
      }
    }
    flippingBook.settings.downloadURL = "<?php print $flippingbook['downloadURL'] ?>";
    
//    if (flippingBook.settings.zoomImagecachePreset) {
//    	flippingBook.settings.zoomPath = "<?php print base_path() . file_directory_path() ?>/imagecache/" + flippingBook.settings.zoomImagecachePreset + "/";
//    	flippingBook.settings.zoomEnabled = true;
//    }
//    else {
//      flippingBook.settings.zoomEnabled = false;
//    }
    
    // define custom book settings here
    <?php print $flippingbook['settings']['jsInitCode']; ?>
    flippingBook.create();
  //--><!]]>
  </script>

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
      <img src="/<?php print $directory ?>/lib/img/btnZoom.gif"    width="36" height="40" border="0" id="fbZoomButton" />
      <img src="/<?php print $directory ?>/lib/img/btnPrint.gif"    width="36" height="40" border="0" id="fbPrintButton" />
      <img src="/<?php print $directory ?>/lib/img/btnDownload.gif" width="36" height="40" border="0" id="fbDownloadButton" />
      <img src="/<?php print $directory ?>/lib/img/btnDiv.gif"      width="13" height="40" border="0" />
      <img src="/<?php print $directory ?>/lib/img/btnPrevious.gif" width="36" height="40" border="0" id="fbBackButton" />
      <img src="/<?php print $directory ?>/lib/img/btnNext.gif"     width="36" height="40" border="0" id="fbForwardButton" />
    </div>
  </div>
  