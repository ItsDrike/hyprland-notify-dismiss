#include "globals.hpp"

/* Find function pointer from the Hyprland binary by it's name.
 *
 * \param[in] name              Simple name of the function (i.e. createGroup)
 * \return  Raw pointer to the found function
 */
void* findHyprlandFunction(const std::string& name);
