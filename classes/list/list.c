#include "list.h"

Data Data_create(int coef, int power) { return (Data) { coef, power }; }

Node* Node_create(Data data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List List_create(Node* left, Node* right, size_t size) { return (List) { left, right, size }; }

void List_push_front(List* list, Data data)
{
    Node* new_node = Node_create(data);

    assert(new_node && "bad alloc");

    if (list->left == NULL && list->right == NULL) {
        list->left = new_node;
        list->right = new_node;
    } else {
        new_node->next = list->left;
        list->left = new_node;
    }
    ++list->size;
}

void List_pop_front(List* list)
{
    assert(list->left && "List is empty");

    Node* del = list->left;
    if (list->size == 1) {
        list->left = NULL;
        list->right = NULL;
    } else {
        list->left = del->next;
    }
    --list->size;
    free(del);
}

void List_push_back(List* list, Data data)
{
    Node* new_node = Node_create(data);

    assert(new_node && "bad alloc");

    if (list->left == NULL && list->right == NULL) {
        list->left = new_node;
        list->right = new_node;
    } else {
        list->right->next = new_node;
        list->right = new_node;
    }
    ++list->size;
}

void List_pop_back(List* list)
{
    assert(list->left && "List is empty");

    Node* del = list->left;
    if (list->size == 1) {
        list->left = NULL;
        list->right = NULL;
    } else {
        Node* cur = list->left;
        while (cur->next->next) {
            cur = cur->next;
        }

        del = cur->next;
        list->right = cur;
    }
    --list->size;
    free(del);
}

void List_erase(List* list, Node* prev_erase)
{
    assert(!(prev_erase == list->right || list->size < 2 || prev_erase == NULL) && "Invalid erase");

    Node* erase = prev_erase->next;
    prev_erase->next = erase->next;
    free(erase);
    --list->size;
    if (prev_erase->next == NULL) {
        list->right = prev_erase;
    }
}

List merge_msort(List* const llist, List* const rlist)
{
    List list = List_create(NULL, NULL, 0);
    Node *itl = llist->left, *itr = rlist->left;
    for (; itl != llist->right->next && itr != rlist->right->next;) {
        if (itl->data.power >= itr->data.power) {
            List_push_back(&list, itl->data);
            itl = itl->next;
        } else {
            List_push_back(&list, itr->data);
            itr = itr->next;
        }
    }
    while (itl != llist->right->next) {
        List_push_back(&list, itl->data);
        itl = itl->next;
    }
    while (itr != rlist->right->next) {
        List_push_back(&list, itr->data);
        itr = itr->next;
    }
    return list;
}

List msort(List* const list)
{
    if (list == NULL || list->size == 0) {
        return List_create(NULL, NULL, 0);
    }
    if (list->size == 1) {
        List temp = List_create(NULL, NULL, 0);
        List_push_back(&temp, list->left->data);
        return temp;
    }

    Node* mid = list->left;
    const size_t halfmid = list->size / 2 - (size_t)(list->size % 2 == 0);
    for (size_t i = 0; i < halfmid; ++i, mid = mid->next)
        ;

    List left = List_create(list->left, mid, 1 + halfmid);
    List right = List_create(mid->next, list->right, list->size - halfmid - 1);
    left = msort(&left);
    right = msort(&right);
    return merge_msort(&left, &right);
}

Node* List_index(const List* const list, const int index) {
    Node *ptr = list->left;
    for (int i = 0; i <= index && ptr != list->right; ++i) {
        assert(ptr->next == NULL && "index out of range");
        ptr = ptr->next;
    }
    return Node_create(ptr->data);
}

void List_glue(List* const dest, List* glued)
{
    assert(dest && "destination is NULL");
    assert(glued && "glued is NULL");

    for (Node *ptr = glued->left; ptr != glued->right;) {
        dest->right->next = ptr;
        dest->right = ptr;

        assert(ptr->next && "index out of range");
        ptr = ptr->next;
    }

    glued->left = NULL;
    glued->right = NULL;
    glued->size = 0;
}