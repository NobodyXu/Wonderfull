// Please install https://github.com/maniacbug/StandardCplusplus by first downloading the whole repo as a zip,
// then goto arudino IDE to install it.

#include <algorithm>
#include <new>
#include <utility>
#include <vector>

template <class T>
class unique_ptr {
    T *ptr;

public:
    unique_ptr(T *p) noexcept:
        ptr{p}
    {}

    unique_ptr(unique_ptr &&other) noexcept:
        ptr{other.ptr}
    {
        other.ptr = NULL;
    }

    unique_ptr& operator = (unique_ptr &&other) noexcept {
        delete ptr;
        ptr = other.ptr;
        other.ptr = NULL;
    }

    T& operator * () const noexcept {
        return *ptr;
    }

    T* operator -> () const noexcept {
        return ptr;
    }

    ~unique_ptr() {
        delete ptr;
    }
};

class event {
public:
    using time_t = unsigned long long;

protected:
    // The return value signals whether the events is preserved after callback
    using callback_t = bool (*)(event&);
    
    unsigned long long time_left; // in millis

    event(time_t scheduled_time):
        time_left{scheduled_time}
    {}

    event& operator = (const event &other) {
        time_left = other.time_left;
    }

public:
    bool operator < (const event &other) const {
        return time_left < other.time_left;
    }

    virtual bool run_callback() = 0;
};

class scheduler {
    std::vector<unique_ptr<event>> queue;

    void sort() {
        std::sort(queue.begin(), queue.end(), [](auto &x, auto &y) noexcept {
            return *x < *y;
        });
    }
    
public:
    scheduler() {
    }

    void add_event(unique_ptr<event> &&e) {
        queue.push(std::move(e));
        sort();    
    }

    void schedule() {
        if (queue[0].time_left < 1) {
            if (queue[0].run_callback())
                sort();
            else
                queue.erase(queue.begin());
        }
    }
};

class music_event: public event {
    class music {
        unsigned int freq;
        typename event::time_t duration;

    public:
        music(unsigned int freq_arg, typename event::time_t duration_arg):
            freq{freq_arg}, duration{duration_arg}
        {}
    };

    static const music the_music[] = {
        music(900, 15),
        music(300, 20),
    };

    unsigned pin;
    unsigned i;

public:
    music_event(unsigned pin_to_use):
        event{0}, i{0}, pin{pin_to_use}
    {
        pinMode(pin, OUTPUT);
    }

    bool run_callback() {
        tone(pin, the_music[i].freq, the_music[i].duration);
        event::time_left = the_music[i].duration;
        ++i;
        return true;
    }
};

class light_event: public event {
    unsigned pin;
    bool is_on;
    
public:
    light_event(unsigned pin_to_use) noexcept:
        event{0}, pin{pin_to_use}, is_on{false]
    {
        pinMode(pin, OUTPUT);
    }

    bool run_callback() {     
        if (is_on == false) {
            digitalWrite(pin, HIGH);
            is_on = true;
            event::time_left = 200;
        } else {
            digitalWrite(pin, LOW);
        }
    }
}

void loop() {
    ;
}
