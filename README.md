# glint.h

## Usage

```C
void my_glint_callback(uint16_t port) {
    // do somthing with the port
}

int main() {
  glint *g = glint_new(my_glint_callback);

  // start the server with a port retrieved automatically
  glint_start(g)

  // access the server using the port
  client_connect('127.0.0.1', g.port);

  // cleanup the server process
  glint_cleanup(g);
}
```

## See Also

* [Test::TCP](https://metacpan.org/pod/Test::TCP)
* [glint](https://github.com/kentaro/glint)

## Author

Kentaro Kuribayashi

## License

MIT