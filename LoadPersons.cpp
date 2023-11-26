struct DBParams {
    string_view name;
    int connection_timeout;
    bool allow_exceptions;
    DBLogLevel db_log_level;
}

struct SearchParams {
    int min_age;
    int max_age;
    string_view name_filter;
}

vector<Person> LoadPersons(DBParams db_params, SearchParams src_params) {
    DBConnector connector(db_params.allow_exceptions, db_params.log_level);
    DBHandler db;
    if (db_params.name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_params.name, db_params.connection_timeout);
    } else {
        db = connector.Connect(db_params.name, db_params.connection_timeout);
    }
    if (!db_params.allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << src_params.min_age << " and "s << src_params.max_age << " "s
              << "and Name like '%"s << db.Quote(src_params.name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}