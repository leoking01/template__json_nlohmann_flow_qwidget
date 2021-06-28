#include "test.h"

#pragma execution_character_set("utf-8")
using json = nlohmann::json;


Test::Test()
{
}

//--------------------------------------------------------------
#if 0
struct MyContainer {
    void advance(){ }
    const char& get_current()
    {
        return  'a';
    }
};

struct MyIterator {
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = const char*;
    using reference = const char&;
    using iterator_category = std::input_iterator_tag;

    MyIterator& operator++() {
        //        target->advance();
        return *this;
    }

    bool operator!=(const MyIterator& rhs) const {
        return rhs.target != target;
    }

    reference operator*() const {
        return target->get_current();
    }

    MyContainer* target = nullptr;
};

MyIterator begin(MyContainer& tgt) {
    return MyIterator{&tgt};
}

MyIterator end(const MyContainer&) {
    return {};
}

void foo() {
    MyContainer c;
    json j = json::parse(c);
}
#endif



namespace ns {
// a simple struct to model a person
struct person {
    std::string name;
    std::string address;
    int age;
};
}

void  some()
{
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

    // convert to JSON: copy each value into the JSON object
   nlohmann:: json j;
    j["name"] = p.name;
    j["address"] = p.address;
    j["age"] = p.age;

    // ...
    {
        // convert from JSON: copy each value from the JSON object
        ns::person p {
            j["name"].get<std::string>(),
                    j["address"].get<std::string>(),
                    j["age"].get<int>()
        };
    }

    {
        // create a person
        ns::person p {"Ned Flanders", "744 Evergreen Terrace", 60};
        // conversion: person -> json
        ////        json j = p;
        //         json j  =  p;
        ////         to_json<  person >(  j,  p  );
        //        std::cout << j << std::endl;
        //        // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}
        //        // conversion: json -> person
        //         json j  ;
        //        auto p2 = j.get<ns::person>();
        //        // that's it
        //        assert(p == p2);
       nlohmann::  json j ;

        nlohmann::adl_serializer< std::string   > ss;
        //  nlohmann::adl_serializer< std::string,std::string> :: to_json <nlohmann::json, ns::person > (p );
    }
}


#if 0
using nlohmann::json;

namespace ns {
template<    typename  Tp>   //   person
void to_json(json& j, Tp& p) {
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}
template<    typename  Tp>   //   person
void from_json(const json& j, Tp  & p) {
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
}
} // namespace ns
#endif


//using nlohmann::json;

namespace ns {
void to_json( nlohmann::json& j, const person& p) {
    j =  nlohmann::json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

void from_json(const  nlohmann::json& j, person& p) {
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
}
} // namespace ns


nlohmann::adl_serializer< std::string   >   serial   ;

nlohmann::adl_serializer< std::string   > ss ;


//template <typename T>
//struct adl_serializer {
//    static void to_json(json& j, const T& value) {
//        // calls the "to_json" method in T's namespace
//    }

//    static void from_json(const json& j, T& value) {
//        // same thing, but with the "from_json" method
//    }
//};

//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

// for convenience


int  main__00002()
{
   nlohmann:: json j2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {"answer", {
             {"everything", 42}
         }},
        {"list", {1, 0, 2}},
        {"object", {
             {"currency", "USD"},
             {"value", 42.99}
         }}
    };

    //---------------------------------------------------------------------
    // a way to express the empty array []
  nlohmann::  json empty_array_explicit = json::array();

    // ways to express the empty object {}
    json empty_object_implicit = json({});
    json empty_object_explicit = json::object();

    // a way to express an _array_ of key/value pairs [["currency", "USD"], ["value", 42.99]]
    json array_not_object = json::array({ {"currency", "USD"}, {"value", 42.99} });

    //---------------------------------------------------------------------
    // create object from string literal
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    // or even nicer with a raw string literal
    auto j22 = R"(
               {
               "happy": true,
               "pi": 3.141
               }
               )"_json;


    //---------------------------------------------------------------------
    // explicit conversion to string
    std::string s = j.dump();    // {"happy":true,"pi":3.141}

    // serialization with pretty printing
    // pass in the amount of spaces to indent
    std::cout << j.dump(4) << std::endl;
    // {
    //     "happy": true,
    //     "pi": 3.141
    // }
    //     return   0;

    //---------------------------------------------------------------------
    if( 1 )
    {
        // write prettified JSON to another file
        std::ofstream o("pretty.json");
        o << std::setw(4) << j22 << std::endl;


        // read a JSON file
        std::ifstream i("pretty.json");
        json j;
        i >> j;
        std::cout <<"j.dump(4) = "<<    j.dump(4) << std::endl;

    }


    //---------------------------------------------------------------------
    {
        std::vector<std::uint8_t> v = {'t', 'r', 'u', 'e'};
        json j = json::parse(v.begin(), v.end());
    }

    {
        std::vector<std::uint8_t> v = {'t', 'r', 'u', 'e'};
        json j = json::parse(v);
    }
    return   0;
}


