# using-autotools

Example of using Autotools to build a C project

## Compile

```bash
autoreconf --install --force
./configure # or ./configure --enable-debug
make
```

## Run

Open a terminal and run the server:

```bash
./whoisserver
```

Open another terminal and run the client:

```bash
./whoisclient localhost:10496 whois google.com
```

## Clean

```bash
make clean
```
