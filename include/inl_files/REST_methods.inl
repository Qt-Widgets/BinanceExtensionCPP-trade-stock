#include "../Binance_Client.h"

// RestSession inline methods


inline void RestSession::get_timeout(unsigned long interval)
{
	curl_easy_setopt(this->_get_handle, CURLOPT_TIMEOUT, interval);
};

inline void RestSession::post_timeout(unsigned long interval)
{
	curl_easy_setopt(this->_post_handle, CURLOPT_TIMEOUT, interval); 
};

inline void RestSession::put_timeout(unsigned long interval)
{
	curl_easy_setopt(this->_put_handle, CURLOPT_TIMEOUT, interval);
};

inline void RestSession::delete_timeout(unsigned long interval)
{
	curl_easy_setopt(this->_delete_handle, CURLOPT_TIMEOUT, interval); 
};