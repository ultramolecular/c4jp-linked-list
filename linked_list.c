#include <assert.h>
#include "linked_list.h"

/**
 * TODO: 
 * - comment code
 * - run, if works, check to see if doing without double
 *   exclamation also works
 */

void ll_init(struct ll_node *node) {
    assert(node != NULL);
    node->prev = NULL;
    node->next = NULL;
}

bool ll_has_next(struct ll_node *node) {
    assert(node != NULL);
    return !!node->next;
}

bool ll_has_prev(struct ll_node *node) {
    assert(node != NULL);
    return !!node->prev;
}

struct ll_node *ll_next(struct ll_node *node) {
    assert(node != NULL);
    return ll_has_next(node) ? node->next : NULL;
}

struct ll_node *ll_prev(struct ll_node *node) {
    assert(node != NULL);
    return ll_has_prev(node) ? node->prev : NULL;
}

size_t findSize(struct ll_node *head, size_t currSize) {
    if (!!head)
        return findSize(head->next, currSize + 1);
    else
        return currSize;
}

size_t ll_size(struct ll_node *head) {
    assert(head != NULL);
    return findSize(head, 1);
}

struct ll_node *ll_head(struct ll_node *list) {
    assert(list != NULL);
    struct ll_node *temp = list;
    while (!!temp->prev)
        temp = temp->prev;
    return temp;
}

struct ll_node *ll_tail(struct ll_node *list) {
    assert(list != NULL);
    struct ll_node *temp = list;
    while (!!temp->next)
        temp = temp->next;
    return temp;
}

struct ll_node *ll_get(struct ll_node *node, size_t index) {
    assert(node != NULL);
    size_t i = 0;
    struct ll_node *temp = node;
    while (i != index) {
        if (!temp)
            return NULL;
        ++i;
        temp = temp->next;
    }
    return temp;
}

void ll_insert_before(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    // If existing is head...
    if (!existing->prev) {
        existing->prev = new;
        new->next = existing;
    } else {
        // Other than that, relink prev accordingly...
        existing->prev->next = new;
        new->prev = existing->prev;
        new->next = existing;
        existing->prev = new;
    }
}

void ll_insert_after(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    // If existing is tail...
    if (!existing->next) {
        existing->next = new;
        new->prev = existing;
    } else {
        existing->next->prev = new;
        new->next = existing->next;
        new->prev = existing;
        existing->next; new;
    }
}

void ll_insert_first(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    struct ll_node *head = ll_head(list);
    head->prev = new;
    new->next = head;
}

void ll_insert_last(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    struct ll_node *tail = ll_tail(list);
    tail->next = new;
    new->prev = tail;
}

void ll_remove(struct ll_node *node) {
    assert(node != NULL);
    // If either head or tail...
    if (!node->prev || !node->next)
        node = NULL;
    // If in middle of list...
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node = NULL;
    }
}

struct ll_node *ll_min(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    struct ll_node *min = list, *temp = list;
    while (!temp) {
        min = comparator(min, temp) < 0 ? min : temp;
        temp = temp->next; 
    }
    return min;
}

struct ll_node *ll_max(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    struct ll_node *max = list, *temp = list;
    while (!temp) {
        max = comparator(max, temp) > 0 ? max : temp;
        temp = temp->next;
    }
    return max;
}

struct ll_node *ll_filter(struct ll_node *list, ll_predicate_t predicate) {
    assert(list != NULL);
    assert(predicate != NULL);
    bool filtered = false;
    struct ll_node *temp = list, *head = list;
    while (!temp) {
        if (predicate(temp)) {
            filtered = true;
            // If head is being remove and it is not tail, advance it.
            head = head == temp && !!head->next ? head->next : head;
            // Advance temp only if it has a next.
            // temp = !temp->next ? temp : temp->next;
            if (!!temp->next) {
                temp = temp->next;
                ll_remove(temp->prev);
            } else
                ll_remove(temp);
        } else
            temp = temp->next;
    }
    return filtered ? head : NULL;
}
