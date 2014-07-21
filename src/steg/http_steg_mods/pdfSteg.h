/* Copyright 2011, 2012 SRI International
 * See LICENSE for other credits and copying information
 */

#ifndef _PDFSTEG_H
#define _PDFSTEG_H

// These are the public interface.

int http_server_PDF_transmit(PayloadServer* pl, struct evbuffer *source,
                             conn_t *conn);
int http_handle_client_PDF_receive(steg_t *s, conn_t *conn,
                                   struct evbuffer *dest,
                                   struct evbuffer* source);

// These are exposed only for the sake of unit tests.

ssize_t pdf_add_delimiter(const char *inbuf, size_t inbuflen,
                          char *outbuf, size_t outbuflen,
                          char delimiter1, char delimiter2);

ssize_t pdf_remove_delimiter(const char *inbuf, size_t inbuflen,
                             char *outbuf, size_t outbuflen,
                             char delimiter1, bool *endFlag, bool *escape);

ssize_t pdf_wrap(const char *data, size_t dlen,
                 const char *pdfTemplate, size_t plen,
                 char *outbuf, size_t outbufsize);

ssize_t pdf_unwrap(const char *data, size_t dlen,
                   char *outbuf, size_t outbufsize);




class PDFSteg : public FileStegMod
{

public:


 /**
compute the capcaity of the cover by getting a pointer to the
beginig of the body in the response

@param cover_body pointer to the begiing of the body
@param body_length the total length of message body
*/
    virtual ssize_t headless_capacity(char *cover_body, int body_length);
    static unsigned int static_headless_capacity(char *cover_body, int body_length);

    /**
returns the capacity of the data you can store in jpeg response
given the jpeg file content in

@param buffer: the buffer containing the payload
@param len: the buffer's length

@return the capacity that the buffer can cover or < 0 in case of error
*/
virtual unsigned int capacity(const uint8_t *buffer, size_t len);
static unsigned int static_capacity(char *buffer, int len);

    /**
constructor just to call parent constructor
*/
    PDFSteg(PayloadServer* payload_provider, double noise2signal = 0); //pdf template in here or as struct member from payload_provider->?

    virtual int encode(uint8_t* data, size_t data_len, uint8_t* cover_payload, size_t cover_len);
    
     virtual ssize_t decode(const uint8_t* cover_payload, size_t cover_len, uint8_t* data);


};


#endif

