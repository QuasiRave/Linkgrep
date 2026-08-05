# Linkgrep
A Linux command-line utility written in C for exploring file relationships.
It can locate symbolic links and hard links, trace back to their target files and show links associated with a given file. 


## Features
- Shows file name, inode, link count, file type and softlinks/hardlinks or target file location.

### Build
*gcc -g main.c filetype.c link_probe.c fs_traverse.c -o linkgrep*   

#### Usage
./linkgrep *target_file_path* *directory_to_find_links*
Eg: ./linkgrep /bin/gcc /bin 


