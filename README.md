# TorFisher
 Tor network mapper. Collect domains, relationships between them and metadata. Does not index content. Simple and minimalist, made in C++
 
## Usage 
 
```console
[me@server]$ ./TorFisher -h
Usage: TorFisher -s seedFile.txt -l logFile.log -t torFile.log -p localhost:8118
Options:
	-s,	Seed, default file is SeedFile.txt. Seed file is mandatory
	-l,	Log, default file is TorFisher.log
	-t,	Tor, default file is TorList.log
	-p,	Proxy, default is localhost:8118
	-h,	Help, this info

```


## Example of a seed file 
 
```console
[me@server]$ cat SeedFile.txt 
zqktlwi4fecvo6ri.onion
3g2upl4pq6kufc4m.onion
...

```


## Start the program with the seed file [mandatory]

```console
me@server]$ ./TorFisher -s SeedFile.txt
10-05-20 20:00:24 [INFO] TorFisher START 
10-05-20 20:00:24 [INFO] |- Seed (-s): SeedFile.txt
10-05-20 20:00:24 [INFO] |- Log (-l): TorFisher.log
10-05-20 20:00:24 [INFO] |- Tor (-t): TorList.log
10-05-20 20:00:24 [INFO] |- Proxy (-p): localhost:8118
10-05-20 20:00:24 [INFO] Reading SeedFile.txt START
10-05-20 20:00:24 [DEBUG] Working phase: Reading seed
10-05-20 20:00:24 [DEBUG] Loading: zqktlwi4fecvo6ri.onion ...status: 200
10-05-20 20:00:26 [DEBUG] Relative link found: wiki/index.php/Main_Page
10-05-20 20:00:24 [INFO] Domain: zqktlwi4fecvo6ri.onion
10-05-20 20:00:24 [INFO] |- Title: Hello!
10-05-20 20:00:24 [INFO] |- Status: 200
10-05-20 20:00:24 [INFO] |- Header: Connection close
10-05-20 20:00:24 [INFO] |- Header: Content-Type text/html; charset=UTF-8
10-05-20 20:00:24 [INFO] |- Header: Date Sun, 10 May 2020 20:00:25 GMT
10-05-20 20:00:24 [INFO] |- Header: Server nginx
10-05-20 20:00:24 [INFO] |- Header: Transfer-Encoding chunked
10-05-20 20:00:24 [INFO] |- DomainCount: 0
10-05-20 20:00:24 [INFO] |- LinkCount: 1
10-05-20 20:00:26 [INFO] TorFisher database status (sites/links): 0 / 1 Scanned successfully (online): 1
10-05-20 20:00:24 [DEBUG] Working phase: Reading seed
10-05-20 20:00:26 [DEBUG] Loading: 3g2upl4pq6kufc4m.onion ...status: 200
10-05-20 20:00:30 [DEBUG] Relative link found: about
10-05-20 20:00:30 [DEBUG] Relative link found: favicon.ico
10-05-20 20:00:30 [DEBUG] Relative link found: manifest.json
10-05-20 20:00:30 [DEBUG] Relative link found: o1894.css
10-05-20 20:00:30 [DEBUG] Relative link found: s1894.css
10-05-20 20:00:26 [INFO] Domain: 3g2upl4pq6kufc4m.onion
10-05-20 20:00:26 [INFO] |- Title: DuckDuckGo — Privacy, simplified.
10-05-20 20:00:26 [INFO] |- Status: 200
10-05-20 20:00:26 [INFO] |- Header: Accept-Ranges bytes
10-05-20 20:00:26 [INFO] |- Header: Cache-Control no-cache
10-05-20 20:00:26 [INFO] |- Header: Connection close
10-05-20 20:00:26 [INFO] |- Header: Content-Length 5425
10-05-20 20:00:26 [INFO] |- Header: Content-Security-Policy default-src https: blob: data: 'unsafe-inline' 'unsafe-eval'; frame-ancestors 'self'
10-05-20 20:00:26 [INFO] |- Header: Content-Type text/html; charset=UTF-8
10-05-20 20:00:26 [INFO] |- Header: Date Sun, 10 May 2020 20:00:29 GMT
10-05-20 20:00:26 [INFO] |- Header: ETag "5eb9ed64-1531"
10-05-20 20:00:26 [INFO] |- Header: Expect-CT max-age=0
10-05-20 20:00:26 [INFO] |- Header: Expires Sun, 10 May 2020 20:00:28 GMT
10-05-20 20:00:26 [INFO] |- Header: Referrer-Policy origin
10-05-20 20:00:26 [INFO] |- Header: Server nginx
10-05-20 20:00:26 [INFO] |- Header: Strict-Transport-Security max-age=0
10-05-20 20:00:26 [INFO] |- Header: Vary Accept-Encoding
10-05-20 20:00:26 [INFO] |- Header: X-Content-Type-Options nosniff
10-05-20 20:00:26 [INFO] |- Header: X-Frame-Options SAMEORIGIN
10-05-20 20:00:26 [INFO] |- Header: X-XSS-Protection 1;mode=block
10-05-20 20:00:26 [INFO] |- DomainCount: 0
10-05-20 20:00:26 [INFO] |- LinkCount: 5
10-05-20 20:00:30 [INFO] TorFisher database status (sites/links): 0 / 6 Scanned successfully (online): 2
10-05-20 20:00:24 [INFO] Reading SeedFile.txt OK
10-05-20 20:00:30 [INFO] TorFisher database status (sites/links): 0 / 6 Scanned successfully (online): 2
10-05-20 20:00:30 [DEBUG] Working phase: Loading link
10-05-20 20:00:30 [DEBUG] Loading: zqktlwi4fecvo6ri.onion/wiki/index.php/Main_Page ...status: 200
10-05-20 20:00:30 [DEBUG] Domain found: 25xxxxxxxxxxxxf3.onion
10-05-20 20:00:30 [DEBUG] Domain found: 2ixxxxxxxxxxxx2w.onion
10-05-20 20:00:30 [DEBUG] Domain found: 2kxxxxxxxxxxxxbu.onion
10-05-20 20:00:30 [DEBUG] Domain found: 2kxxxxxxxxxxxxpv.onion
10-05-20 20:00:30 [DEBUG] Domain found: 2oxxxxxxxxxxxxez.onion
10-05-20 20:00:30 [DEBUG] Domain found: 2qxxxxxxxxxxxx7j.onion
...
10-05-20 20:00:30 [DEBUG] Domain found: zexxxxxxxxxxxx36y.onion
10-05-20 20:00:30 [DEBUG] Domain found: zqxxxxxxxxxxxxgb.onion
10-05-20 20:00:30 [DEBUG] Domain found: zqxxxxxxxxxxxxri.onion
10-05-20 20:00:30 [DEBUG] Domain found: zqxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxad.onion
10-05-20 20:00:30 [DEBUG] Domain found: zvxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxqd.onion
10-05-20 20:00:30 [DEBUG] Link found: elxxxxxxxxxxxxvy.onion/binfo_check_anonymity.php
10-05-20 20:00:30 [DEBUG] Link found: elxxxxxxxxxxxxvy.onion/fakeid.php
10-05-20 20:00:30 [DEBUG] Link found: iaxxxxxxxxxxxxzz.onion/index.php/forums/thread/385/35
10-05-20 20:00:30 [DEBUG] Link found: kpxxxxxxxxxxxxz2.onion/files.html
10-05-20 20:00:30 [DEBUG] Link found: lixxxxxxxxxxxxay.onion/wiki/
10-05-20 20:00:30 [DEBUG] Link found: lixxxxxxxxxxxxpa.onion/im/jappix/
10-05-20 20:00:30 [DEBUG] Link found: ocxxxxxxxxxxxxgn.onion/wiki/
10-05-20 20:00:30 [DEBUG] Link found: poxxxxxxxxxxxx6h.onion/wiki/index.php
10-05-20 20:00:30 [DEBUG] Link found: xixxxxxxxxxxxxko.onion/tor
10-05-20 20:00:30 [DEBUG] Link found: zqxxxxxxxxxxxxri.onion/wiki/index.php/Main_Page
10-05-20 20:00:30 [DEBUG] Link found: zqxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxad.onion/wiki/Link_proposals
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Anonymity
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Bible
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Contact_Directory
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Dead_services
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Email
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Federation_OnionNet
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/How_to_Exit_the_Matrix
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/In_Praise_Of_Hawala
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Korean_Hidden_Wiki
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Libraries
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Main_Page
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/OnionCat_BitTorrent
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/OnionCat_BitTorrent_Tracker
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/OnionCat_Gnutella
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/OnionCat_Instructions
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/OnionNet
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/P2P_Bandwidth
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Pidgin
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Political_Advocacy
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Privacy
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Security
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Siterules
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/SnapBBSIndex
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Tails
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Terrific_Strategies_To_Apply_A_Social_media_Marketing_Approach
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/The_Matrix
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/TorChat
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/Verifying_PGP_signatures
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/opensearch_desc.php
10-05-20 20:00:30 [DEBUG] Relative link found: wiki/resources/favicon.ico
10-05-20 20:00:30 [INFO] Domain: zqktlwi4fecvo6ri.onion
10-05-20 20:00:30 [INFO] |- Title: The Hidden Wiki
10-05-20 20:00:30 [INFO] |- Status: 200
10-05-20 20:00:30 [INFO] |- Header: Cache-Control private, must-revalidate, max-age=0
10-05-20 20:00:30 [INFO] |- Header: Connection close
10-05-20 20:00:30 [INFO] |- Header: Content-Language en
10-05-20 20:00:30 [INFO] |- Header: Content-Type text/html; charset=UTF-8
10-05-20 20:00:30 [INFO] |- Header: Date Sun, 10 May 2020 20:00:30 GMT
10-05-20 20:00:30 [INFO] |- Header: Expires Thu, 01 Jan 1970 00:00:00 GMT
10-05-20 20:00:30 [INFO] |- Header: Last-Modified Thu, 30 Apr 2020 20:18:54 GMT
10-05-20 20:00:30 [INFO] |- Header: Server nginx
10-05-20 20:00:30 [INFO] |- Header: Transfer-Encoding chunked
10-05-20 20:00:30 [INFO] |- Header: Vary Accept-Encoding, Cookie
10-05-20 20:00:30 [INFO] |- Header: X-Content-Type-Options nosniff
10-05-20 20:00:30 [INFO] |- DomainCount: 188
10-05-20 20:00:30 [INFO] |- LinkCount: 41
10-05-20 20:00:31 [INFO] TorFisher database status (sites/links): 188 / 46 Scanned successfully (online): 2
10-05-20 20:00:31 [DEBUG] Working phase: Loading link
10-05-20 20:00:31 [DEBUG] Loading: 3g2upl4pq6kufc4m.onion/about ...status: 200
10-05-20 20:00:34 [DEBUG] Relative link found: favicon.ico
10-05-20 20:00:34 [DEBUG] Relative link found: hiring
10-05-20 20:00:34 [DEBUG] Relative link found: manifest.json
10-05-20 20:00:34 [DEBUG] Relative link found: s1894.css
10-05-20 20:00:34 [DEBUG] Relative link found: t1894.css
10-05-20 20:00:31 [INFO] Domain: 3g2upl4pq6kufc4m.onion
10-05-20 20:00:31 [INFO] |- Title: About DuckDuckGo
10-05-20 20:00:31 [INFO] |- Status: 200
10-05-20 20:00:31 [INFO] |- Header: Accept-Ranges bytes
10-05-20 20:00:31 [INFO] |- Header: Cache-Control no-cache
10-05-20 20:00:31 [INFO] |- Header: Connection close
10-05-20 20:00:31 [INFO] |- Header: Content-Length 32403
10-05-20 20:00:31 [INFO] |- Header: Content-Security-Policy default-src https: blob: data: 'unsafe-inline' 'unsafe-eval'; frame-ancestors 'self'
10-05-20 20:00:31 [INFO] |- Header: Content-Type text/html; charset=UTF-8
10-05-20 20:00:31 [INFO] |- Header: Date Sun, 10 May 2020 20:00:33 GMT
10-05-20 20:00:31 [INFO] |- Header: ETag "5eb9ed65-7e93"
10-05-20 20:00:31 [INFO] |- Header: Expect-CT max-age=0
10-05-20 20:00:31 [INFO] |- Header: Expires Sun, 10 May 2020 20:00:32 GMT
10-05-20 20:00:31 [INFO] |- Header: Referrer-Policy origin
10-05-20 20:00:31 [INFO] |- Header: Server nginx
10-05-20 20:00:31 [INFO] |- Header: Strict-Transport-Security max-age=0
10-05-20 20:00:31 [INFO] |- Header: Vary Accept-Encoding
10-05-20 20:00:31 [INFO] |- Header: X-Content-Type-Options nosniff
10-05-20 20:00:31 [INFO] |- Header: X-Frame-Options SAMEORIGIN
10-05-20 20:00:31 [INFO] |- Header: X-XSS-Protection 1;mode=block
10-05-20 20:00:31 [INFO] |- DomainCount: 0
10-05-20 20:00:31 [INFO] |- LinkCount: 5
10-05-20 20:00:34 [INFO] TorFisher database status (sites/links): 188 / 48 Scanned successfully (online): 2
...
```
## Prerequisites

https://www.openssl.org

https://www.boost.org

## Proxy

For example, a working proxy is https://github.com/dperson/torproxy
