//
// Created by Abhijeet Mahajan on 9/21/19.
//

#ifndef CONTAINER_IN_C_ABHIJEET_MAHAJAN_DEQUE_HPP
#define CONTAINER_IN_C_ABHIJEET_MAHAJAN_DEQUE_HPP

#define Deque_DEFINE(t)                                                                                           \
struct Deque_##t##_Iterator {                                                                                     \
    t* index;                                                                                                     \
    t* head;                                                                                                      \
    t* tail;                                                                                                      \
    int status;                                                                                                   \
                                                                                                                  \
    void (*inc)(Deque_##t##_Iterator *iterator);                                                                  \
    void (*dec)(Deque_##t##_Iterator *iterator);                                                                  \
    t& (*deref)(Deque_##t##_Iterator *iterator);                                                                  \
    bool (*Deque_##t##_Iterator_equal) (Deque_##t##_Iterator iterator, Deque_##t##_Iterator other);               \
};                                                                                                                \
                                                                                                                  \
t* tail_index(Deque_##t##_Iterator *iterator){                                                                  \
    return iterator->tail - 1;                                                                                    \
}                                                                                                                 \
                                                                                                                  \
void inc(Deque_##t##_Iterator *iterator) {                                                                        \
    t* t_index = tail_index(iterator);                                                                          \
    iterator->index = iterator->index == t_index ? iterator->head :  iterator->index +1;                          \
}                                                                                                                 \
                                                                                                                  \
void dec(Deque_##t##_Iterator *iterator) {                                                                        \
    t* t_index = tail_index(iterator);                                                                          \
    iterator->index = iterator->index == iterator->head ? t_index : iterator->index - 1;                          \
}                                                                                                                 \
                                                                                                                  \
t& deref(Deque_##t##_Iterator *iterator) {                                                                       \
    t* t_index = tail_index(iterator);                                                                          \
    return iterator->status == 1 ? (iterator->index == t_index ? *(iterator->head) : *(iterator->index + 1)) : (iterator->index == iterator->head ? *(t_index) : *(iterator->index));\
}                                                                                                                 \
                                                                                                                  \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator iterator, Deque_##t##_Iterator other) {                      \
    t* t_index = tail_index(&iterator);                                                                         \
    return iterator.status == 1 ? (iterator.index == t_index ? iterator.head == other.index : iterator.index + 1 == other.index) : (iterator.index == iterator.head ? iterator.tail - 1 == other.index : iterator.index - 1 == other.index);\
}                                                                                                                 \
                                                                                                                  \
struct Deque_##t {                                                                                                \
    struct Deque_##t##_Iterator *start_iterator;                                                                  \
    struct Deque_##t##_Iterator *end_iterator;                                                                    \
                                                                                                                  \
    t *array;                                                                                                     \
    int current_size;                                                                                             \
    size_t array_limit;                                                                                           \
    char type_name[6 + sizeof #t]= "Deque_" #t;                                                                   \
                                                                                                                  \
                                                                                                                  \
    void (*push_back)(Deque_##t *, t);                                                                            \
    void (*push_front)(Deque_##t *, t);                                                                           \
    void (*pop_front)(Deque_##t *);                                                                               \
    void (*pop_back)(Deque_##t *);                                                                                \
    t& (*front)(Deque_##t *);                                                                                     \
    t& (*back)(Deque_##t *);                                                                                      \
    t& (*at)(Deque_##t *, size_t);                                                                                \
    void (*clear)(Deque_##t *);                                                                                   \
    bool (*empty)(Deque_##t *);                                                                                   \
                                                                                                                  \
    size_t (*size)(Deque_##t *);                                                                                  \
    void (*dtor)(Deque_##t *);                                                                                    \
    bool (*less_by_id)(const t &, const t &);                                                                     \
    void (*reallocate)(Deque_##t *);                                                                              \
                                                                                                                  \
    Deque_##t##_Iterator &(*begin)(Deque_##t *);                                                                  \
    Deque_##t##_Iterator &(*end)(Deque_##t *);                                                                    \
                                                                                                                  \
    bool (*Deque_##t##_equal)(Deque_##t o1, Deque_##t o2);                                                        \
    void (*sort)(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);                                        \
};                                                                                                                \
                                                                                                                  \
bool Deque_##t##_equal(Deque_##t o1, Deque_##t o2) {                                \
    if (o1.current_size != o2.current_size)                                                                       \
        return false;                                                                                             \
                                                                                                                  \
    for (size_t i = 0; i < o1.current_size; i++) {                                                                \
        if (o1.less_by_id(o1.at(&o1, i), o2.at(&o2, i)))                                                          \
            return false;                                                                                         \
        else if(o2.less_by_id(o2.at(&o2, i), o1.at(&o1, i)))                                                     \
            return false; \
    }                                                                                                             \
    return true;                                                                                                  \
}                                                                                                                 \
                                                                                                                  \
void dtor(Deque_##t *iterator) {                                                                                  \
    free(iterator->array);                                                                                        \
    free(iterator->start_iterator);                                                                               \
    free(iterator->end_iterator);                                                                                 \
}                                                                                                                 \
                                                                                                                  \
size_t size(Deque_##t *iterator) {                                                                                \
    return iterator->current_size;                                                                                \
}                                                                                                                 \
                                                                                                                  \
bool empty(Deque_##t *iterator) {                                                                                 \
    return iterator->current_size == 0;                                                                           \
}                                                                                                                 \
                                                                                                                  \
void reallocate(Deque_##t *iterator) {                                                                            \
    int modified_limit = iterator->array_limit + iterator->array_limit;                                           \
    iterator->array_limit =modified_limit;                                                                        \
                                                                                                                  \
    t* modified_array = (t *) malloc(sizeof(t) * iterator->array_limit);                                          \
                                                                                                                  \
    struct Deque_##t##_Iterator *new_head_it = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));     \
    struct Deque_##t##_Iterator *new_tail_it = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));     \
    int size = iterator->current_size;                                                                            \
                                                                                                                  \
    new_head_it->index = modified_array;                                                                          \
    new_tail_it->index = modified_array + size;                                                                   \
                                                                                                                  \
    new_head_it->head = new_tail_it->head = modified_array;                                                       \
    new_head_it->tail = new_tail_it->tail =  modified_limit + modified_array ;                                    \
                                                                                                                  \
    std::copy(&(iterator->front(iterator)), iterator->start_iterator->tail, new_head_it->index);                  \
    std::copy(iterator->start_iterator->head, (&(iterator->back(iterator)) + 1),                                  \
              new_head_it->index + (iterator->end_iterator->tail - iterator->start_iterator->index) - 1);         \
                                                                                                                  \
    iterator->dtor(iterator);                                                                                     \
    iterator->array = modified_array;                                                                             \
                                                                                                                  \
    iterator->start_iterator = new_head_it;                                                                       \
    iterator->start_iterator->index = new_head_it->tail - 1;                                                      \
    iterator->start_iterator->head = iterator->array;                                                             \
    iterator->start_iterator->tail = iterator->array + modified_limit;                                            \
    iterator->start_iterator->inc = &inc;                                                                         \
    iterator->start_iterator->dec = &dec;                                                                         \
    iterator->start_iterator->deref = &deref;                                                                     \
    iterator->start_iterator->Deque_##t##_Iterator_equal = &Deque_##t##_Iterator_equal;                           \
    iterator->start_iterator->status = 1;                                                                         \
                                                                                                                  \
    iterator->end_iterator = new_tail_it;                                                                         \
    iterator->end_iterator->head = iterator->array;                                                               \
    iterator->end_iterator->tail = iterator->array + modified_limit;                                              \
    iterator->end_iterator->inc = &inc;                                                                           \
    iterator->end_iterator->dec = &dec;                                                                           \
    iterator->end_iterator->deref = &deref;                                                                       \
    iterator->end_iterator->index = new_tail_it->head + size;                                                     \
    iterator->end_iterator->status = 0;                                                                           \
    iterator->end_iterator->Deque_##t##_Iterator_equal = &Deque_##t##_Iterator_equal;                             \
}                                                                                                                 \
                                                                                                                  \
t& front(Deque_##t *iterator) {                                                                                   \
    t* t_index = tail_index(iterator->start_iterator);                                                          \
    return (iterator->start_iterator->index == t_index) ?  *(iterator->start_iterator->head) : *(iterator->start_iterator->index + 1);   \
}                                                                                                                 \
                                                                                                                  \
t& back(Deque_##t *iterator) {                                                                                    \
    return  (iterator->end_iterator->index == iterator->end_iterator->head) ? *(iterator->end_iterator->tail - 1) : *(iterator->end_iterator->index - 1); \
}                                                                                                                 \
                                                                                                                  \
Deque_##t##_Iterator &begin(Deque_##t *iterator) {                                                                \
    return *iterator->start_iterator;                                                                             \
}                                                                                                                 \
                                                                                                                  \
Deque_##t##_Iterator &end(Deque_##t *iterator) {                                                                  \
    return *(iterator->end_iterator);                                                                             \
}                                                                                                                 \
                                                                                                                  \
void check_for_reallocation(Deque_##t *iterator){                                                                 \
    if (iterator->current_size == iterator->array_limit)                                                          \
        iterator->reallocate(iterator);                                                                           \
}                                                                                                                 \
                                                                                                                  \
void push_back(Deque_##t *iterator, t item) {                                                                     \
    *iterator->end_iterator->index = item;                                                                        \
    iterator->end_iterator->index = iterator->end_iterator->index == iterator->end_iterator->tail - 1 ? iterator->array : (iterator->end_iterator->index +1); \
    iterator->current_size += 1;                                                                                  \
    check_for_reallocation(iterator);                                                                             \
}                                                                                                                 \
                                                                                                                  \
void push_front(Deque_##t *iterator, t item) {                                                                    \
    *iterator->start_iterator->index = item;                                                                      \
    iterator->start_iterator->index =  (iterator->start_iterator->index == iterator->start_iterator->head) ? (iterator->start_iterator->tail - 1) : (iterator->start_iterator->index - 1);  \
    iterator->current_size++;                                                                                     \
    check_for_reallocation(iterator);                                                                             \
}                                                                                                                 \
                                                                                                                  \
void pop_back(Deque_##t *iterator) {                                                                              \
    dec(iterator->end_iterator);                                                                                  \
    iterator->current_size -= 1;                                                                                  \
}                                                                                                                 \
                                                                                                                  \
void pop_front(Deque_##t *iterator) {                                                                             \
    inc(iterator->start_iterator);                                                                                \
    iterator->current_size -= 1;                                                                                  \
}                                                                                                                 \
                                                                                                                  \
t& at(Deque_##t *iterator, size_t i) {                                                                            \
    if (&iterator->front(iterator) + i > iterator->end(iterator).tail - 1) {                                      \
        i -= iterator->end_iterator->tail - &iterator->front(iterator) - 1;                                       \
        return *(iterator->array + i);                                                                            \
    }                                                                                                             \
    return *(&iterator->front(iterator) + i);                                                                     \
}                                                                                                                 \
                                                                                                                  \
bool (*t##_cmp)(const t & o1, const t & o2);                                                                      \
extern "C"                                                                                                        \
int Deque_##t##_cmp(const void *o1, const void *o2, void *) {                                                             \
    if (t##_cmp(*((t *) o2), *((t *) o1))){                                                                        \
        return 1;       \
    }                                                                                          \
    else if (t##_cmp(*((t *) o1), *((t *) o2))) { \
            return -1;  \
    } \
    else                                                                                                          \
        return 0;                                                                                                 \
}                                                                                                                 \
                                                                                                                  \
void sort(Deque_##t *iterator, Deque_##t##_Iterator begin, Deque_##t##_Iterator end) {                            \
    t* buffer = (t *) malloc(sizeof(t) * iterator->array_limit);                                                  \
    size_t i = 0;                                                                                                 \
    if (iterator->begin(iterator).tail != end.index)                                                              \
        end.inc(&end);                                                                                            \
    for (auto it = begin; !Deque_##t##_Iterator_equal(it, end); it.inc(&it)) {                                    \
        buffer[i] = *it.index;                                                                                    \
        i++;                                                                                                      \
    }                                                                                                             \
    qsort_r(buffer, i, sizeof(t), &Deque_##t##_cmp, nullptr);                                                                \
    i = 0;                                                                                                        \
    for (auto it = begin; !Deque_##t##_Iterator_equal(it, end); it.inc(&it), i++) {                               \
    *it.index = buffer[i];                                                                                    \
    }                                                                                                             \
    free(buffer);                                                                                                 \
}                                                                                                                 \
                                                                                                                  \
void clear(Deque_##t *iterator);                                                                                  \
                                                                                                                  \
void Deque_##t##_ctor(Deque_##t *iterator, bool (*less)(const t &, const t &)) {                                  \
    iterator->current_size = 0;                                                                                   \
    iterator->array_limit = 10;                                                                                   \
    iterator->start_iterator = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));                     \
    iterator->end_iterator = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));                       \
    iterator->array = (t *) malloc(sizeof(t) * iterator->array_limit);                                            \
    iterator->start_iterator->index = iterator->array;                                                            \
    iterator->end_iterator->index = iterator->array + 1;                                                          \
    iterator->end_iterator->head = iterator->array;                              \
    iterator->start_iterator->head =  iterator->array;                              \
    iterator->end_iterator->tail = iterator->array + iterator->array_limit;    \
    iterator->start_iterator->tail =   iterator->array + iterator->array_limit;      \
    iterator->end_iterator->inc = &inc;                                             \
    iterator->start_iterator->inc = &inc;                                           \
     iterator->end_iterator->dec = &dec;                                            \
    iterator->start_iterator->dec = &dec;                                           \
    iterator->end_iterator->deref = &deref;         \
    iterator->start_iterator->deref = &deref;                                     \
    iterator->start_iterator->Deque_##t##_Iterator_equal = &Deque_##t##_Iterator_equal;                           \
    iterator->end_iterator->Deque_##t##_Iterator_equal = &Deque_##t##_Iterator_equal;                             \
    iterator->start_iterator->status = 1;                                                                         \
    iterator->end_iterator->status = 0;                                                                           \
    iterator->size = &size;                                                                                       \
    iterator->less_by_id = less;                                                                                  \
    iterator->dtor = &dtor;                                                                                       \
    iterator->empty = &empty;                                                                                     \
    iterator->push_back = &push_back;                                                                             \
    iterator->push_front = &push_front;                                                                           \
    iterator->pop_front = &pop_front;                                                                             \
    iterator->pop_back = &pop_back;                                                                               \
    iterator->reallocate = &reallocate;                                                                           \
    iterator->front = &front;                                                                                     \
    iterator->back = &back;                                                                                       \
    iterator->begin = &begin;                                                                                     \
    iterator->end = &end;                                                                                         \
    iterator->at = &at;                                                                                           \
    iterator->clear = &clear;                                                                                     \
    iterator->Deque_##t##_equal = &Deque_##t##_equal;                                                             \
    iterator->sort = &sort;                                                                                       \
    t##_cmp = less;                                                                                               \
}                                                                                                                 \
                                                                                                                  \
void clear(Deque_##t *iterator) {                                                                                 \
    iterator->dtor(iterator);                                                                                     \
    Deque_##t##_ctor(iterator, iterator->less_by_id);                                                             \
}
#endif //CONTAINER_IN_C_ABHIJEET_MAHAJAN_DEQUE_HPP
                                                                                                                  