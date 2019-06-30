
/**
2.1
    Compute the max difference

A robot needs to travel along a path that includes several ascents and descents. When
it goes up, it uses its battery to power the motor and when it descends, it recovers
the energy which is stored in the battery. The battery recharging process is ideal:
on descending, every Joule of gravitational potential energy converts to a Joule of
electrical energy which is stored in the battery. The battery has a limited capacity
and once it reaches this capacity, the energy generated in descending is lost.

Problem 2.1 : Design an algorithm that takes a sequence of n three-dimensional
coordinates to be traversed, and returns the minimum battery capacity needed to
complete the journey. The robot begins with the battery fully charged.
 */

#include <vector>
#include <limits>

int FindBatteryCapacity(const std::vector<int> &h)
{
    int min_height = std::numeric_limits<int>::max(), capacity = 0;

    for (const auto &height : h)
    {
        capacity = std::max(capacity, height - min_height);
        min_height = std::min(min_height, height);
    }

    return capacity;
}

int main(int argc __attribute((unused)), char const *argv[] __attribute((unused)))
{
    return 0;
}
