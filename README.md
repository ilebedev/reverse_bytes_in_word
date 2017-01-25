# reverse_bytes_in_word
Portable tool to reverse the order of bytes in the words of a file or stream, given a number of byte per word

## Usage
 
    reverse_bytes_in_word <int bytes per word> [in file (defaults to stdin)] [out file (defaults to stdout)]

## Examples

Below, each character is a single byte, `reverse_bytes_in_word` reverses the charactes of each word.

Reversing 1-byte words has no effect:
  
    echo "01234567" | reverse_bytes_in_word 1
  
    >1234567

Reversing 4-byte words will reverse each sequence of 4 characters:

    echo "01234567" | reverse_bytes_in_word 1
    
    >32107654

Leftover bytes (incomplete words) are dropped.
  
    echo "012345678" | reverse_bytes_in_word 1
    
    >32107654

The tool works for an arbitrary number of bytes per word:

    echo "012345678" | reverse_bytes_in_word 1
    >32107654
  
To change endianness of a binary file with 32-bit words:

    echo "deadbeef01234567" > in_hex
    xxd -r -p in_hex in
    reverse_bytes_in_word 4 in out
    xxd -c 4 -p out
    
    >efbeadde
    67452301

## How to Install

Pretty much as you would expect:

    make
    sudo make install

This builds the tool with GCC (-O3), and copies the binary to /usr/bin/reverse_bytes_in_word

## How to Uninstall

    sudo rm /usr/bin/reverse_bytes_in_word
    
