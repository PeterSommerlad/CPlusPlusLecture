This project only exists to introduce new/delete syntax. 

DO NOT USE neither new nor delete in your own classes or code
use unique_ptr/make_unique or shared_ptr/make_shared instead.

...unless you are implementing your own version of standard library like 
classes, such as variant<T> or optional<T> that might require 
placement new.