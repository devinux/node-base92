const fs = require('fs');
const path = require('path');
const { encode, decode } = require('../src');
describe('encode test', () => {
  it('input params is string', () => {
    expect(encode('Hello World')).toMatch(';K_$aOTbKnsM*k');
  });
  it('input params is buffer', () => {
    expect(encode(fs.readFileSync(path.join(__dirname, './encode')))).toMatch(';K_$aOTbKnsM*k');
  });
  it('input params is empty', () => {
    expect(() => {
      encode();
    }).toThrow('One argument required - buffer or string with data to encode');
  });
  it('input params is not string or buffer', () => {
    expect(() => {
      encode(1);
    }).toThrow('Argument should be a buffer or a string');
  });
});

describe('decode test', () => {
  it('input params is string', () => {
    expect(decode(';K_$aOTbKnsM*k')).toMatch('Hello World');
  });
  it('input params is buffer', () => {
    expect(decode(fs.readFileSync(path.join(__dirname, './decode')))).toMatch('Hello World');
  });
  it('input params is empty', () => {
    expect(() => {
      decode();
    }).toThrow('One argument required - buffer or string with data to encode');
  });
  it('input params is not string or buffer', () => {
    expect(() => {
      decode(1);
    }).toThrow('Argument should be a buffer or a string');
  });
});
