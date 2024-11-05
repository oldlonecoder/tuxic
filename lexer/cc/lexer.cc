//
// Created by oldlonecoder on 24-03-08.
//

#include <tuxic/lexer/lexer.h>

namespace tux
{



log::code lexer::exec()
{
    log::debug() << " Verify config data:";
    if(!m_config.production)
    {
        log::error() << " config data is empty!";
        return log::code::null_ptr;
    }



    log::debug() << " Now Building the Tokens Reference Table:";
    m_config.production->set_reference_table();
    if(m_config.text.empty() || m_config.production->reference_table().empty())
    {
        log::error() << " config data is empty!";
        return log::code::empty;
    }

    log::debug() << " Here is the ref_table Table Dump:" ;
    m_config.production->dump_reference_table();

    //return log::code::Ok;

    scanner = m_config.text;
    scanner.skip_ws();

    return loop();
}


/*!
 * @brief Virtual loop
 *
 * @return log::code::Code...
 */
log::code lexer::loop()
{
    log::debug() << "Before entering the loop: ";
    log::out() << " scanner position set at (col:" << scanner()-scanner.begin() << "):{" << scanner.mark() << log::fn::endl << "}";
    log::test() << " now entering in the loop:";
    //return log::code::Ok;
    auto Cursor = scanner(); // Save current position.
    while(!scanner.eof() && (state != log::code::eof))
    {
        log::debug() << " lexer::loop [Next Token]: " << scanner.mark();
        lex_token Token{};
        if(!tokenize(m_config.production->scan(scanner())))
        {
            log::debug() << log::fn::func << " token not in table: " << scanner.mark();
            if(!!tokenize_numeric(Token))
            {
                if(scanner.eof() || (state == log::code::eof))
                    return log::code::accepted;
            }
        }

        if(Cursor == scanner())
        {
            log::error() << " loop: no scanning (unhandled yet or bug ;) )" << log::fn::endl << scanner.mark();
            return log::code::rejected;
        }

        Cursor = scanner();
    }

    return log::code::accepted;

}




log::code lexer::tokenize(lex_token Token)
{
    log::debug() << log::fn::func << scanner.mark(); //not scanned yet that's why it doen's have line and col numbers ...yet

    static std::map<lex::type::T, log::code (lexer::*)(lex_token&)> ScanFn = {
        {lex::type::Binary           , &lexer::tokenize_binary_operator},
        {lex::type::Null             , &lexer::tokenize_default},
        {lex::type::Unary            , &lexer::tokenize_unary_operator},
        {lex::type::Punc             , &lexer::tokenize_punctuation},
        {lex::type::Keyword          , &lexer::tokenize_keyword},
        {lex::type::Text             , &lexer::tokenize_string},
        {lex::type::Prefix           , &lexer::tokenize_prefix},
        {lex::type::Postfix          , &lexer::tokenize_postfix},
        {lex::type::LineComment      , &lexer::tokenize_cpp_comment},
        {lex::type::BlocComment      , &lexer::tokenize_comment_bloc}
    };

    log::code r{log::code::rejected};
    for(auto [T, Fn] : ScanFn)
    {
        if(T & Token.sem)
           return (this->*Fn)(Token);
    }
    return r;
}




log::code lexer::tokenize_binary_operator(lex_token &newtoken)
{
    log::debug() << newtoken.details() << scanner.mark();
    (void)tokenize_sign_prefix(newtoken);
    newtoken.token_location = scanner.sync();
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken); // s'occupera de mettre à jour le token et d'avancer le tscanner. ;)

    return log::code::accepted;
}

log::code lexer::tokenize_default(lex_token &newtoken)
{
    log::debug() << " entering with:" << (newtoken ? newtoken.details() : scanner.mark());

    log::debug() << " test scannumber:";
    // auto r = scanner.scannumber();
    // if(!!r.first)
    // {
    //     newtoken.num_data = new tux::StrScanner::Numeric::details{R.second};
    //     newtoken.token_location = scanner.Sync();
    //     newtoken.token_location.length = newtoken.num_data->Seq.length();
    //     newtoken.token_location.begin  = newtoken.num_data->Seq.begin();
    //     newtoken.token_location.end    = newtoken.num_data->Seq.end();
    //     newtoken.Prim       =lex::type::Number;
    //     newtoken.name       = lex::lexem::Numeric;
    //     state = scanner.Step(static_cast<int32_t>(newtoken.num_data->Seq.length()));
    //     newtoken.numeric_tr();
    //     (*m_config.production) << newtoken;
    //     state = scanner.SkipWS() ? log::code::Eof : log::code::Ok;
    //     log::debug() << "Pushed: " << newtoken.details();
    // }
    //else
    //{
        // auto [Ic,C] = Enums::ReturnCodeAttributes(R.first);
        // log::debug() << " ScanNumber:" << C << Ic << Enums::ToString(R.first);
        // log::debug() << " test scan identifier token:";
    return tokenize_identifier(newtoken);
    //}
   // return log::code::Accepted;
}


log::code lexer::tokenize_unary_operator(lex_token &newtoken)
{
    newtoken.token_location = scanner.sync();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    log::debug() << newtoken.details();
    push_token(newtoken);
    log::debug() << "pushed: " << newtoken.details();
    return log::code::accepted;
}

log::code lexer::tokenize_punctuation(lex_token &newtoken)
{
    log::debug() << log::fn::func << " sync'ing the scanner:";
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    log::debug() << "pushing new [punctuation] token";
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken);
    log::debug() << "pushed: " << log::fn::func << newtoken.details();
    return log::code::accepted;
}

log::code lexer::tokenize_keyword(lex_token &newtoken)
{
    log::debug() << " sync'ing the scanner:";
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    log::debug() << "pushing new [keyword] token";
    push_token(newtoken);
    log::debug() << "pushed: " << newtoken.details();
    return log::code::accepted;
}


log::code lexer::tokenize_string(lex_token &newtoken)
{
    return log::code::ok;
}


log::code lexer::tokenize_identifier(lex_token &newtoken)
{
    log::debug() << scanner(); //scanner.Mark();
    auto i = scanner.scan_identifier();
    if(!i.first) return i.first;


    log::debug() << " Fill newtoken Numeric literal Infos (scanner's LocationData -> newtoken::location_data):";
    newtoken.token_location = scanner.sync();
    newtoken.token_location.length = i.second.length();
    newtoken.token_location.begin = i.second.begin();
    newtoken.token_location.end = i.second.end() - 1;
    newtoken.name    = lex::lexem::Identifier;
    newtoken.prim    =lex::type::Id;
    newtoken.sem     =lex::type::Id|lex::type::Leaf;
    newtoken.flags = { .V = 1 };
    log::debug() << "Pushing New [Identifier] Token";
    (*m_config.production) << newtoken;
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    scanner.skip_ws();
    log::debug() << "Pushed: " << newtoken.details();

    return log::code::accepted;
}

log::code lexer::tokenize_sign_prefix(lex_token &newtoken)
{
    log::debug() << log::fn::func << ":";
    if ((newtoken.m != lex::mnemonic::Sub) && (newtoken.m != lex::mnemonic::Add))
    {
        log::out() << " rejected (not subtract or addition operator).";
        return log::code::rejected;
    }
    
    if(!m_config.production->empty())
    {
        auto &token = m_config.production->production_table().back();
        log::out() << "prev: " << token.details(true);
        if((!token.has_type(lex::type::Binary |lex::type::Punc)) || (token.m == lex::mnemonic::ClosePar))
        {
            log::out() << " rejected: previous token is not an operator or a expression-terminating punctuation token";
            return log::code::rejected;
        }
    }

    log::out() << " conditions met for unary prefix sign operator:";
    newtoken.prim =lex::type::Sign;
    newtoken.sem = (newtoken.sem & ~(lex::type::Postfix|lex::type::Binary)) | lex::type::Prefix |lex::type::Unary | lex::type::Operator| lex::type::Sign;
    newtoken.m = lex::mnemonic::Negative;
    newtoken.token_location.length = 1;
    newtoken.token_location.end = newtoken.token_location.begin + 1;
    return log::code::accepted;
}



/*!
 * @brief tokenize prefix operator after verifying that the prefix-operator is well formed and does not break the arithmetic syntax rules
 * @param newtoken
 *
 * @note a * *B;
 * @return log::code::Code
 */
log::code lexer::tokenize_prefix(lex_token &newtoken)
{
    if ((newtoken.m == lex::mnemonic::Decr) || (newtoken.m == lex::mnemonic::Incr) || (newtoken.m == lex::mnemonic::BinaryNot))
    {
        if(production().empty())
        {
            push_token(newtoken);
            return log::code::accepted;
        }
        if((production().back().flags.V) && (!production().back().has_type(lex::type::Operator)))
        {
            newtoken.prim   = lex::type::Postfix;
            newtoken.sem    &= ~lex::type::Prefix |lex::type::Postfix;
            if(newtoken.m   == lex::mnemonic::BinaryNot)
                newtoken.m  = lex::mnemonic::Factorial;
        }
        if(!production().back().flags.V)
            throw log::syntax() << newtoken.details() << ": illegal;";
    }
    push_token(newtoken);
    
    return log::code::accepted;
}




log::code lexer::tokenize_postfix(lex_token &newtoken)
{

    if((production().empty()) || (!production().back().flags.V))
        throw log::syntax() << newtoken.details() << ": Illegal;";

    push_token(newtoken);
    
    return log::code::ok;
}

log::code lexer::tokenize_cpp_comment(lex_token &newtoken)
{
    return log::code::ok;
}

log::code lexer::tokenize_comment_bloc(lex_token &newtoken)
{
    return log::code::ok;
}


log::code lexer::tokenize_numeric(lex_token& newtoken)
{
    auto R = scanner.scan_number();
    if(!!R.first)
    {
        newtoken.num_data = tux::sscan::numeric::details{R.second};
        newtoken.token_location = scanner.sync();
        newtoken.token_location.length = newtoken.num_data.seq.length();
        newtoken.token_location.begin  = newtoken.num_data.seq.begin();
        newtoken.token_location.end    = newtoken.num_data.seq.end();
        newtoken.prim       =lex::type::Number;
        newtoken.name       = lex::lexem::Numeric;
        state = scanner.step(static_cast<int32_t>(newtoken.num_data.seq.length()));
        newtoken.numeric_tr();
        (*m_config.production) << newtoken;
        state = scanner.skip_ws() ? log::code::eof : log::code::ok;
        
        return log::code::accepted;
    }
    return log::code::rejected;
}


/*!
 * @brief
 * @param Token
 *
 * @todo Assign location data here.
 */
void lexer::push_token(lex_token &newtoken)
{
    log::debug() << " Pushing newtoken : " << log::fn::endl  << newtoken.details();

    (*m_config.production) << newtoken;
    
    //scanner.Sync(newtoken.token_location.length);
    log::debug() << "SkipWS: ";
    scanner.skip_ws();
}

lex_token::list& lexer::production()
{
    return m_config.production->ref_table;
}

void lexer::update_token_location(lex_token &newtoken)
{

}




} // lex
