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
}

void ICircularBufferRepository_close(void)
{
}

static FILE *auxiliary_open(char *prefix, char *suffix)
{
}

int ICircularBufferRepository_open(char *name)
{
}

int ICircularBufferRepository_append(circular_buffer cb)
{
}
