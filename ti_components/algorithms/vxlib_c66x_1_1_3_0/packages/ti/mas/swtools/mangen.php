<?php
/*********************************************************************************************************
*
* Module
*   mangen
*
* Description
*   Create an HTML Manifest given an XML one.
*
* Change Log
*
* March 21st, 2010  Jack Manbeck  Created
*
************************************************************************************************************/

/*  TODO

1. Where do we store te style sheets mangen uses. Assumed to be local to the script for now.
2. Not sure we should use the product name and verson as part of the manifets html name as the guideline suggests.
*/

/************************************************************************************************************
* Include other PHP support scripts
************************************************************************************************************/
        
/************************************************************************************************************
*   GLOBALS
*
* Note: To use a global in a function you must declare it is  "global" within the function scope.
************************************************************************************************************/
$option_filter  = True;   /* If false, do not display the private block in the Package Node */
$option_silent  = False;  /* If True, do not display any errors.. xml object will spew on badly formed XML */


/************************************************************************************************************
*   Class Definitions
************************************************************************************************************/

/************************************************************************************************************
*   Function Definitions
************************************************************************************************************/

/* 
** Returns True if the string has a value. 
*/
function hasvalue($val) {
  if (!$val) return 0;
  if ($val == "") return 0;
  return 1; 
}


/*
** prints program usage.
*/
function usage() {

  echo "usage: mangen.php [Options] [Outfile] [path/]manifest.xml" ."\n";
  echo "Options" ."\n";
  echo "  -help     : Displays usage and then exits" ."\n";
  echo "  -nofilter : Creates a manifest that includes the private portion." ."\n";
  echo "  -silent   : Dont output anything, even errors." ."\n";
  echo "               Caveat: Badly formed XML will spew - ensure proper syntax." ."\n";
  echo "Htmlfile    : (optional) Provide specific Manifest file name." ."\n";
  echo "               Default: [Product.name]_[Product.version]_Manifest.html" ."\n";

  return; 
}

/*
** Prints an error (unless silent is set) and then exits.
*/
function error_and_die($errmsg) {
  global $option_silent;
  
  if (!$option_silent) echo $errmsg . "\n";
  exit (1); 
}

/************************************************************************************************************
* This area starts the "main" of the PHP script
*************************************************************************************************************/

  date_default_timezone_set("America/New_York");

  /* 
  ** $argc is the count of arguments, $argv are the arguments.
  **
  ** e.g. php-cli manifest.php has $argc = 1 and argv[0] = "manifest.php"
  ** e.g. php-cli manifest.php nofilter has $argc = 2 and argv[0] = "manifest.php" and argv[1] = "nofilter"
  */

  /*
  ** Check any command line arguments. Valid arguments are:
  **
  **  -help     - displays usage .
  **  -nofilter   - creates a manifest that includes the private portion.
  **  -silent   - Dont output anything, even errors. Caveat: Badly formed XML will spew so make sure the syntax is good.
  **
  */
  if ($argc < 2) {
    /* Need at least two arguments */
    usage();
    exit(1);
  }

  /* Parse the options if specified. The name of this script is always the first argument so skip it */
  for ($i=1; $i < $argc; $i++) {
    if (strcasecmp($argv[$i], "-silent") == 0) {
      $option_silent = True;
    }
    else
    if (strcasecmp($argv[$i], "-nofilter") == 0) {
      $option_filter = False;
    }
    else
    if ($argv[$i][0] != '-' && $i < ($argc - 1)) {
      $htmlfn = $argv[$i];
    }
    else
    if (strcasecmp($argv[$i], "-help") == 0) {
      usage();
      exit (1);
    }
  }

  /* Get the name of the file to convert from the command line.. should always be the last argument */
  $xmlfilename = $argv[$argc-1];

  /* Make sure the file exists */
  if (!file_exists($xmlfilename)) {
    error_and_die("The XML file you specified ( " . $xmlfilename . " ) could not be found. ");
  }

  /* Open the XML Manifest */
  $xmlDoc = new DOMDocument();
  $xmlDoc->load($xmlfilename);

  if (!$xmlDoc ) {
    error_and_die("The name of the XML Manifets you specified could not be found");
  }

  /* 
  ** Get some key variables from the manifest.
  */
  $x = $xmlDoc->documentElement;

  /* 
  ** Get the product name and version so we can title the HTML file
  */
  $prodname = "";
  $prodver  = "";

  $products = $xmlDoc->getElementsByTagName('product');

  foreach ($products AS $product) {
    $children = $product->childNodes;
    foreach ($children as $child) {
      if (strcasecmp($child->nodeName, "name") == 0) {
        $prodname = $child->nodeValue;
      }
      else 
      if (strcasecmp($child->nodeName, "version") == 0) {
        $prodver = $child->nodeValue;
      }
    }
  }

  if (!hasvalue($prodname) || !hasvalue($prodver)) {
    error_and_die("You must specify both a product name and version in the <product> block.");
  }

  /* 
  ** Get the XMl manifest version number so we can select the right style sheet 
  */
  $stylever = "1.00.00.00"; /* use this as the default if XML doesnt specify */

  $vernode  = $xmlDoc->getElementsByTagName('manifestversion');
  if ($vernode->length) {
    $stylever = $vernode->item(0)->nodeValue;
  }
    
  /* 
  ** Get the style sheet. We have one for filtered views and one for unfiltered views 
  */
  if ($option_filter) {
    $filter = "";
  }
  else {
    $filter = "_unfilter";
  }

  $xslDoc = new DOMDocument();
  $stylename = "manifest_style_" . $stylever . $filter . ".xsl";
  $stylepath = dirname($_SERVER['PHP_SELF']) . DIRECTORY_SEPARATOR . $stylename;
  $xslDoc->load($stylepath);
      
  /* 
  ** Generate the HTML and save it to a file. We create it in the same directory as the XML file.
  */
  $proc = new XSLTProcessor();
  $proc->importStylesheet($xslDoc);

  /* Set html output file name */
  if (!hasvalue($htmlfn)) {
    $htmlfn = $prodname ."_" . $prodver . "_Manifest.html";
  }

  /* Prepend directory path if present */
  $xmlpath  = dirname($xmlfilename);
  $htmlpath = dirname($htmlfn);
  if (hasvalue($xmlpath) && !hasvalue($htmlpath)) {
    $htmlfn = $xmlpath . "\\" . $htmlfn;
  }

  $fp = fopen($htmlfn, "w");
  fwrite($fp, $proc->transformToXML($xmlDoc));
  fclose($fp);

  /* 
  ** Record the conversion 
  */
  if (!$option_silent) {
    $text = "Generated manifest " . $htmlfn . " from " . $xmlfilename . " using style sheet " . $stylename;
    echo $text;
  }

  exit (0);

?>