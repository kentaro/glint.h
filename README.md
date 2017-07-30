# glint.h

## Usage

```C
void my_glint_callback(uint16_t port) {
    // do somthing with the port
}

int main() {
  glint *g = glint_new(my_glint_callback);

  // start the server with a port retrieved automatically
  if (!glint_start(g)) {
    perror("failed to start the server");
    exit(1);
  }

  // access the server using the port
  client_connect('127.0.0.1', g.port);

  // cleanup the server process
  glint_stop(g);
}
```

## See Also

* [Test::TCP](https://metacpan.org/pod/Test::TCP)
* [glint](https://github.com/kentaro/glint)

## Author

Kentaro Kuribayashi

## License

MIT