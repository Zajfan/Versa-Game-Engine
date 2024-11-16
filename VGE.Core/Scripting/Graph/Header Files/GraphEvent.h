#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <any>

class Event
{
public:
    enum class EventType
    {
        Undefined,
        Collision,
        Trigger,
        ButtonClicked,
        // ... add other event types as needed
    };

    Event(EventType type, const std::string& sender = "", const std::any& data = std::any());

    EventType Type() const { return type_; }
    const std::string& Sender() const { return sender_; }
    const std::any& Data() const { return data_; }

private:
    EventType type_;
    std::string sender_;
    std::any data_;
};

#endif // EVENT_H