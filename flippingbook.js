$(document).ready(function() {
	if (window.Drupal && Drupal.settings.flippingbook) {
		var data = Drupal.settings.flippingbook;
		var settings = Drupal.parseJson(data.settings);
		
		$.extend(flippingBook.settings, Drupal.parseJson(data.settings));
		
		flippingBook.contents = data.contents;
		flippingBook.pages    = data.pages;
		
		// define custom book settings here
		flippingBook.settings.bookWidth = 1000;
		flippingBook.settings.bookHeight = 667;
		flippingBook.settings.pageBackgroundColor = 0xc2c2c2; // baksiden av boka
		flippingBook.settings.backgroundColor = 0xb3b3b3;
		flippingBook.settings.zoomUIColor = 0x919d6c;
		flippingBook.settings.useCustomCursors = false;
		flippingBook.settings.dropShadowEnabled = false,
		flippingBook.settings.zoomImageWidth = 1061;
		flippingBook.settings.zoomImageHeight = 1472;
		flippingBook.settings.downloadURL = "http://dev.front.no/katalog/loplabbet/loplabbet_katalog_v2010.pdf";
		flippingBook.settings.flipSound = "sounds/02.mp3";
		flippingBook.settings.flipCornerStyle = "first page only";
		flippingBook.settings.zoomHintEnabled = false;
		
		flippingBook.settings.downloadURL = data.downloadURL;
		
		flippingBook.create();
		
		console.dir(flippingBook);
	}
});