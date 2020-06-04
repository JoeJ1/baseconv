# baseconv
simple program to convert from one base to another

## usage:
`baseconv [options] (<number> <from> <to>)`  
Convert a <number> <from> one base <to> another.  
  
example: `baseconv '1bfa' 16 10`  
  
options:  
```
-h..........Shows these options in a help menu.      
-c <value>..The character set for conversion (default: 0123456789abcdefghijklmnopqrstuvwxyz).   
-i..........Disables case sensitivity for character set, making all input characters lowercase.
```  
  


## todo:
*reverse output of `dectobase()`
*implement charset validation.
*implement case insensitivity.
