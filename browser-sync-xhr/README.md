# Use EMSCRIPTEN_FETCH_SYNCHRONOUS in Janet custom function to send HTTP(s) requests from inside WASM

## Instructions for this devcontainer

Tested with Janet [v1.34.0](https://github.com/janet-lang/janet/releases/tag/v1.34.0),
 Emscripten [v3.1.61](https://github.com/emscripten-core/emscripten/tree/3.1.61).

### Preparation

1. Open this repo in devcontainer, e.g. using Github Codespaces.
   Type or copy/paste following commands to devcontainer's terminal.

### Building

1. `cd` into the folder of this example:

```sh
cd browser-sync-xhr
```

2. Download `janet.c` and `janet.h` from release into `janet` subfolder. These two files are enough to embed 
 Janet into example program:

```sh
curl -L --compressed --output-dir janet --create-dirs -O "https://github.com/janet-lang/janet/releases/download/v1.34.0/janet.{c,h}"
```

3. Compile the example using Emscripten:

```sh
emcc -I janet janet/janet.c -s FETCH=1 --proxy-to-worker -o main.js main.c
```

This command will output `main.wasm`, `main.js`, and `main.worker.js`. 

### Test with browser

1. Run simple HTTP server to temporarily publish project to Web:

```sh
python3 -m http.server
```

Codespace will show you "Open in Browser" button. Just click that button or
obtain web address from "Forwarded Ports" tab.

2. As `index.html`, JS files, and a **1.3M**-sized `main.wasm` are loaded into browser, refer to browser developer console
   to see the results.


### Finish

Perform your own experiments if desired.
