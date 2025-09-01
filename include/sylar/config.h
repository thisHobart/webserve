#ifndef __SYLAR_CONFIG_H__
#define __SYLAR_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

#include "sylar/log.h"

namespace sylar {

// Base class for configuration variables
class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name, const std::string& description = "")
        :m_name(name), m_description(description) {}
    virtual ~ConfigVarBase() {}

    const std::string& getName() const { return m_name; }
    const std::string& getDescription() const { return m_description; }

    virtual std::string toString() = 0;
    virtual bool fromString(const std::string& val) = 0;
    virtual std::string getTypeName() const = 0;
protected:
    std::string m_name;
    std::string m_description;
};

// Template class for configuration variables
template<class T>
class ConfigVar : public ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVar> ptr;
    typedef std::function<void (const T& old_value, const T& new_value)> on_change_cb;

    ConfigVar(const std::string& name, const T& default_value, const std::string& description = "")
        : ConfigVarBase(name, description), m_val(default_value) {}

    std::string toString() override {
        try {
            return boost::lexical_cast<std::string>(m_val);
        } catch (std::exception& e) {
            // SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception "
            //     << e.what() << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    }

    bool fromString(const std::string& val) override {
        try {
            setValue(boost::lexical_cast<T>(val));
        } catch (std::exception& e) {
            // SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::fromString exception "
            //     << e.what() << " convert: string to " << typeid(m_val).name()
            //     << " - " << val;
            return false;
        }
        return true;
    }

    const T getValue() const { return m_val; }
    void setValue(const T& v) {
        // Here you would implement change notification logic
        m_val = v;
    }
    std::string getTypeName() const override { return typeid(T).name(); }

private:
    T m_val;
};


// Config manager class
class Config {
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
            const T& default_value, const std::string& description = "") {
        // In a real implementation, you would store and manage the created ConfigVar objects.
        // This is a simplified version.
        auto tmp = std::make_shared<ConfigVar<T>>(name, default_value, description);
        return tmp;
    }

    static ConfigVarBase::ptr LookupBase(const std::string& name);
    static void LoadFromYaml(const YAML::Node& root);
};

}

#endif
