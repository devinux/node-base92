# node-base92
### Description
A C++ addon for nodejs supports base92 encoding and decoding.
### Install

```
npm install -S node-base92
```

### Usage

```
const fs = require('fs');
const {encode, decode} = require('node-base92');


// string
encode('Hello World') // should be ;K_$aOTbKnsM*k
// buffer
encode(fs.readFileSync('./inputFile'));
// string
decode(';K_$aOTbKnsM*k') // should be Hello World
// buffer
decode(fs.readFileSync('./inputFile'));
```
### Thanks
thenoviceoof(https://github.com/thenoviceoof) wrote base92
### License
MIT