# glint.h

Spawns an arbitrary TCP server temporarily with an automatically retrieved port.

## Usage

```C
#include "glint.h"

// Assume the server is the target of your integration test
void my_glint_callback(uint16_t port) {
  execl("tests/test-server.rb", "ruby", port, (char *)NULL);
}

int main() {
  glint *g = glint_new(my_glint_callback);

  // start the server with a port retrieved automatically
  if (!glint_start(g)) {
    perror("failed to start the server");
    exit(1);
  }

  // access the server using the port
  your_client_connect('127.0.0.1', g.port);

  // do something with the server

  // cleanup the server process
  glint_stop(g);

  glint_free(g);
}
```

## Types

### `void (*glint_callback)(char *port)`

Callback function to pass `glint *glint_new(glint_callback cb)`. The port number passed as `char *` (for ease).

### struct `glint`

* `uint16_t port`: port number which is automatically retrieved
* `pid_t pid`: process id of a child process (your server process)
* `glint_callback cb`: callback function in which you `exec` your server process

## Methods

### `glint *glint_new(glint_callback)`
### `bool glint_start(glint *self)`
### `void glint_stop(glint *self)`
### `void glint_free(glint *self)`
### `uint16_t glint_empty_port()`

## See Also

* [Test::TCP](https://metacpan.org/pod/Test::TCP)
* [glint](https://github.com/kentaro/glint)

## Author

Kentaro Kuribayashi

## License

MIT