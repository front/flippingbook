  <script type="text/javascript">
  <!--//--><![CDATA[//><!--
    FlippingBook.prototype.create = function(){
      this.settings.pagesSet = this.pages;
      this.settings.zoomPagesSet = this.zoomPages;
      this.settings.printPagesSet = this.printPages;
      
      if( location.hash.substr(1) != "" )
        this.settings.firstPageNumber = location.hash.substr(1);
      Drupal.settings.FlippingBook.path
      this.addLoadEvent( this.onWindowLoad );
      swfobject.embedSWF(
          Drupal.settings.FlippingBook.path + "/FlippingBook.swf",
          this.containerId,
          this.stageWidth,
          this.stageHeight,
          "8.0.0",
          Drupal.settings.FlippingBook.path + "/js/expressInstall.swf",
          this.settings,
          {allowScriptAccess: "always", bgcolor:  "#" + this.settings.backgroundColor.toString( 16 ) }
      );
    };

  
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

    if (flippingBook.settings.flipSound[0] != '/') {
    	flippingBook.settings.flipSound = Drupal.settings.FlippingBook.path + '/' + flippingBook.settings.flipSound;
    }
    
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
  