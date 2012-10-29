var modifyClassName = function (elem, add, string) {
var s = (elem.className) ? elem.className : "";
var a = s.split(" ");
if (add) {
  for (var i=0; i<a.length; i++) {
      if (a[i] == string) {
          return;
          }
      }
  s += " " + string;
  }
else {
    s = "";
    for (var i=0; i<a.length; i++) {
        if (a[i] != string)
            s += a[i] + " "; 
        }
    }
elem.className = s;
}
function toggleGroup(n) {
    //alert(n);
    var currentClass = document.getElementById("myscoretable");
    for (var i=1; i<20; i++) {
      modifyClassName(currentClass,true,"sitehide"+i);
    }
    modifyClassName(currentClass,false,"sitehide"+n);
}
