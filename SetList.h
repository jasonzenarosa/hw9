template <typename T>
class SetList{
    struct ListNode{
        T data;
        ListNode* next;
    public:
        ListNode(T data, ListNode* next){
            this->data = data;
            this->next = next;
        }
    };
    ListNode* head;
public:
    class iterator{
        ListNode* current;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T; //??? this was just T
        using pointer = value_type*;//???
        using reference = value_type&;//???
        using difference_type = ptrdiff_t;

        explicit iterator(ListNode* const ptr = nullptr) : current(ptr){}
        iterator & operator++(){
            current = current->next;
            return *this;
        }
        iterator operator++(int){
            ListNode* tmp = current;
            current = current->next;
            return iterator(tmp);
        }
        reference operator*() const{
            return current->data;
        }
        pointer operator->() const{
            return &(current->data);
        }
        bool operator==(iterator const& other) const{
            return current == other.current;
        }
    };
    static_assert(std::forward_iterator<iterator>); //???
public:
    using value_type = T; //??? do i need to change
    using pointer = value_type*;//???
    using reference = value_type&;//???

    SetList(){
        head = nullptr;
    };
    SetList(SetList const& other){
        this->~SetList();
        if (other.head == nullptr) head = nullptr;
        head = new ListNode(other.head->data, nullptr);
        ListNode* current = other.head->next;
        ListNode* node = head;
        while (current != nullptr){
            node->next = new ListNode(current->data, nullptr);
            node = node->next;
            current = current->next;
        }
    };
    SetList& operator = (SetList const& other){ //???
        if (head != other.head){
            this->~SetList();
            if (other.head == nullptr) head = nullptr;
            head = new ListNode(other.head->data, nullptr);
            ListNode* current = other.head->next;
            ListNode* node = head;
            while (current != nullptr){
                node->next = new ListNode(current->data, nullptr);
                node = node->next;
                current = current->next;
            }
        }
        return *this;
    }
    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(nullptr);
    }
    iterator find(reference value){
        ListNode* current = head;
        while (current != nullptr){
            if (current->data == value){
                return iterator(current);
            }
            current = current->next;
        }
        return iterator(nullptr);
    }
    iterator insert(iterator const, reference value){ //perhaps not find(), perhaps contains()
        if (!find(value)){
            ListNode* new_node = new ListNode(value, head);
            head = new_node;
        }
    }
    ~SetList(){
        ListNode* tmp;
        while (head != nullptr){
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
};