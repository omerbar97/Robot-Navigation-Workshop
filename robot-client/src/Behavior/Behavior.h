//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_BEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_BEHAVIOR_H


/**
 * this is an abstract class for all behaviors, a behavior can be navigating in a hall, or exiting a room or anything else
 * and can be implemented in any way, but it must implement the execute method
 * another kind of behavior is MessageBehavior, which is a behavior that is executed when a message is received or sent
 */
class Behavior {
public:

    /**
     * constructor for the behavior.
     */
    Behavior() = default;

    /**
     * virtual destructor for the behavior. (for the inheritance)
     */
    virtual ~Behavior() = default;

    // each behavior should implement this method
    virtual int execute() = 0;
};

#endif //ROBOT_NAVIGATION_WORKSHOP_BEHAVIOR_H
