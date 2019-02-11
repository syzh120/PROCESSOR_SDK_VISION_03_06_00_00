/* MAIN ROUTINE STARTS HERE */
var redirect_path;

if (arguments.length != 1) {
  print ("USAGE:");
  print ("xs -f redirect.js <relpath>");
  java.lang.System.exit (1);
}

redirect_path = arguments[0];

print ("<html>\n<head>\n");
print ("<meta http-equiv=\"refresh\" content=\"0; url=" + redirect_path + "\">\n");
print ("<meta http-equiv=\"Content-Language\" content=\"en-us\">\n");
print ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\">\n");
print ("<title>Redirect</title>\n");
print ("</head>\n<body>\n</body>\n</html>\n");

