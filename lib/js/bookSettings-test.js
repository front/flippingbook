flippingBook.pages = [
	"pages/1.swf",
	"pages/life_demo2_02.jpg",
	"pages/life_demo2_03.jpg",
	"pages/life_demo2_04.jpg",
	"pages/life_demo2_05.jpg",
	"pages/life_demo2_06.jpg",
	"pages/life_demo2_07.jpg",
	"pages/life_demo2_08.jpg",
	"pages/life_demo2_09.jpg",
	"pages/life_demo2_10.jpg",
	"pages/life_demo2_11.jpg",
	"pages/life_demo2_12.jpg"
];


flippingBook.contents = [
	[ "Forside", 1 ],
	[ "Enhance", 6 ]
];

// define custom book settings here
flippingBook.settings.bookWidth = 826;
flippingBook.settings.bookHeight = 584;
flippingBook.settings.pageBackgroundColor = 0x5b7414; // baksiden av boka
flippingBook.settings.backgroundColor = 0x77a372;
flippingBook.settings.zoomUIColor = 0x919d6c;
flippingBook.settings.useCustomCursors = false;
flippingBook.settings.dropShadowEnabled = false,
flippingBook.settings.zoomImageWidth = 992;
flippingBook.settings.zoomImageHeight = 1403;
flippingBook.settings.downloadURL = "http://imod.front.no/flipmal/ElevationSeriesLaunchBrochureEnglish.pdf";
flippingBook.settings.flipSound = "sounds/02.mp3";
flippingBook.settings.flipCornerStyle = "first page only";
flippingBook.settings.zoomHintEnabled = true;

// default settings can be found in the flippingbook.js file
flippingBook.create();
