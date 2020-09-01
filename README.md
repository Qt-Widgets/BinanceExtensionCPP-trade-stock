BinanceExtensionCPP
=

# Intro 

This library is an extension for the API of Binance. It is used to help write trading algorithms on Binance. 
<br />The design is delibaretly attempting to reduce 'thinking' during runtime, by using clever methods such as CRTP and the `Params` object; no virtual classes/methods are used in this library.
<br /> More performance boosting features are planned to be added in the future. One of them is `constexpr` for string concatenation after the release of C++20.
# Dependencies

	1. JsonCPP https://github.com/open-source-parsers/jsoncpp
	2. CURL 
	3. Boost/Beast websockets https://github.com/boostorg/beast

These 3 must be present in order to use the library.


# Documentation
In order to use this library, you must have all dependencies installed. Afterwards you can simply `#include "include/Binance_Client.h"` and add all content of `/src` directory to the Source files. 
<br />Note that `.inl` files are included inside the main header.
<br /> <br />
<br />You must initialize a client object, which is one of the following: *[SpotClient, FuturesClientUSDT, FuturesClientCoin]*
<br /> In order to use *[Wallet, FuturesWallet, SubAccount, MarginAccount, Savings, Mining]* endpoints, they should be initialized from within other Client classes, by passing the Client object to the constructor.					
i.e: `SpotClient::Wallet my_wallet{ my_client_obj }`. 
<br /> These endpoints each has their own dedicated struct inside 'Client' class.

## Exchange client
If the client is not public, api-key and api-secret must be passed in std::string format to the constructor.
<br />Futures clients may be declared in testnet mode by using the method "set_testnet_mode(bool)". SpotClient has 'test_new_order' method but no testnet mode endpoints.
- #### Exceptions
	WIP
    
- #### CRTP implementation
	The CRTP is implemented as follows:
    <br />
    <br />├── Client
    <br />│        ├── SpotClient
    <br />│        │
    <br />│           └── FuturesClient
    <br />│                │
    <br />│                ├── FuturesClientUSDT
    <br />│                └── FuturesClientCoin
    <br />
    <br /> 
    <br /> 
    As was mentioned earlier, unique endpoints are located as separate structs inside Client.
	<br /> CRTP interface and implementations are separated inside `Binance_Client.cpp`. Generally speaking, implementations are marked by a `v_` prefix.
    <br /> Deeper implementations (i.e `Client` -> `FuturesClient` -> [`FuturesClientUSDT`, `FuturesClientCoin`]) include an additional underscore: `v__`.

- #### Notes
		1. No copy assignment / constructor are implemented for Client classes. Each object has its own unique Session, WS, and running streams...
		2. All unique endpoint structs require that the client object contains keys and is not a public client.

## REST client
- #### 'Params' object
	WIP
- #### Response type
	Each REST request returns a JSON type objet, that holds the three following keys:
    1. "response" = Actual response from the exchange in string format.
    2. "code" = HTTP status code of the request.
    3. "parse_status" = Returns a string generated by the JSON parser, containing parsing errors (if any)
- #### Notes
   		 1. There are four curl handles that are alive throughout the entire life of a RestSession object, one for each request type: PUT, DELETE, POST, GET.
   		 2. In order to avoid race conditions by using the same handle at the same time for different requests, mutex is used.
## Websocket client
- #### Callback functor
	WIP
- #### Stream Manager
	WIP
- #### Notes
		1. Default arguments are not allowed with threads. The argument must be specified
		2. When passing a symbol as an argument to a stream starter, the symbol must be lower case.

### Optimizations
For Microsoft compilers set the following flags for better runtime performance:
* Optimization: /O2
* Instrinsic functions: /Oi
* Favor speed: /Ot
* Frame pointers: /Oy (if available)

# Examples
* orderbook_manager.cpp = Connecting to a symbol orderbook and fetching live data + getting initial snap via REST (not thread-safe).


# Lined up
* constexpr for endpoints + api base after the release of c++20 (support for constexpr and std::string)
