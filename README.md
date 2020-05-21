# PROTATE

A command-line utility that rotates each character in an ASCII text file by a certain order. 
The rotation mechanism is similar to [ROT13](https://en.wikipedia.org/wiki/ROT13). Here, each ASCII character is rotated by its ASCII value.  
Read the [documentation](http://paramsiddharth.github.io/protate).

# Usage

```protate FILE_IN N [-o] [FILE_OUT] [-p] [--h, --help, /?]```

Parameters:
- ```FILE_IN```
    : The input file.
- ```N```
    : The number of ASCII character rotations to do in each character. A negative value would indicate negative rotation.
- ```-o FILE_OUT```
    : Would output the result generated from ```FILE_IN``` to ```FILE_OUT```. If omitted, the output would be written to ```./a.out```.
- ```-p```
    : Previews the output instead of saving it to a file.
- ```--h, --help, /?```
    : Show usage help.

# Building

To build it using ```gcc``` or ```clang```, compile it via the command-line using ```make```.  
```> make protate```

# Examples

The sample file story.txt contains the following text:  
```The rose is red.
A girl is playing there.
There is a playground.
An aeroplane is in the sky.
Numbers are not allowed in the password.
```

- ```> protate 30 story.txt -o hiph0p```   
  Generates text by rotating each character by order +30 and writes the output to ```./hiph0p```.
- ```> protate hiph0p -30 -p```  
  Decrypts the contents of ```./hiph0p``` by rotating it by order -30 and displays it instead of storing it due to the ```-p``` flag. If everything goes well, the output will be same as the original ```story.txt``` file.
- ```> protate hiph0p -30```  
  Decrypts the contents of ```./hiph0p``` by rotating it by order -30, and, since no output file is specified, writes the output to ```./a.out```. If everything goes well, the output will be same as the original ```story.txt``` file.

<p style='text-align: center;'>
    Made with &#9825; by <a href='http://www.paramsid.com'>Param</a>.
</p>
