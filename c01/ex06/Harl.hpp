#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);
        int  levelIndex(const std::string &level) const;

    public:
        Harl();
        ~Harl();
        void filter(std::string level);
};

#endif
