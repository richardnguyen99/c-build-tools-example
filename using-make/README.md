# using-make

Example of using GNU Make to build C projects

## Compile

```bash
make
# or
make debug
```

## Run

Open a terminal and run the server:

```bash
./whoisserver # or ./whoisserver_debug
Server is listening on localhost:10496
```

Open another terminal and run the client:

```bash
./whoisclient localhost:10496 whois google.com
```

## Clean

```bash
make clean
```
