#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "i_circular_buffer_repository.h"
#include "circular_buffer_infra_file_service.h"
#include "i_circular_buffer.h"

#define MAX_RECORD 1024
#define INDEX_SUFFIX ".ndx"
#define DATA_SUFFIX ".rec"
#define FILE_DB_REPO "../Persistence/FileDB/CircularBuffer/CIRCULAR_BUFFER"

struct RECORD_CB
{
    unsigned long data_length;
    int offset_head;
    int offset_current;
    char data[]; //new in c99 !!
};

struct circular_buffer
{
    char *tail;
    unsigned long length;
    char *head;
    char *current;
    bool isFull;
};

struct index
{
    long recordStart;
    size_t recordLength;
};

static FILE *index_stream;
static FILE *data_stream;

int ICircularBufferRepository_save(circular_buffer cb)
{
    if (!ICircularBufferRepository_open(FILE_DB_REPO))
        return 0;
    ICircularBufferRepository_append(cb);   
}

void ICircularBufferRepository_close(void)
{
    fclose(data_stream);
    fclose(index_stream);
}

static FILE *auxiliary_open(char *prefix, char *suffix)
{
    int prlength = strlen(prefix);
    int sulength = strlen(suffix);
    char name[prlength + sulength + 1];
    strncpy(name, prefix, prlength);
    strncpy(name + prlength, suffix, sulength + 1);
    FILE *stream = fopen(name, "r+");
    if (stream == NULL)
    {
        stream = fopen(name, "w+");
    }
    if (stream == NULL)
    {
        perror(name);
    }
    return stream;
}

int ICircularBufferRepository_open(char *name)
{
    data_stream = auxiliary_open(name, DATA_SUFFIX);
    if (data_stream == NULL)
        return 0;
    index_stream = auxiliary_open(name, INDEX_SUFFIX);
    if (index_stream == NULL)
    {
        fclose(index_stream);
        return 0;
    }
    return 1;
}

static struct RECORD_CB calculrecord(circular_buffer cb)
{
    struct RECORD_CB record_cb;
    record_cb.data_length =  sizeof(cb->tail)* cb->length;
    record_cb.offset_head = (cb->head - cb->tail);
    record_cb.offset_current = (cb->current - cb->tail);
    return record_cb;
}


int ICircularBufferRepository_append(circular_buffer cb)
{
    struct index index;
    struct RECORD_CB record_cb;
    record_cb = calculrecord(cb);
    int record[3] = {record_cb.data_length,
                     record_cb.offset_head, record_cb.offset_current};
    size_t length = sizeof(record);
    fseek(data_stream, 0l, SEEK_END);
    index.recordStart = ftell(data_stream);
    index.recordLength = length;
    fwrite(record,sizeof(int),3,data_stream);
    fseek(index_stream, 0L, SEEK_END);
    fwrite(&index,sizeof index, 1, index_stream);
    return 1;
}
