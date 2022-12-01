#include <iostream>

#include <restinio/all.hpp>

#include <json_dto/pub.hpp>


struct bytebattleTeam_t
{
	bytebattleTeam_t() = default;
	
	bytebattleTeam_t(
		std::string teamName,
		std::string fieldOfStudy,
        std::string time )
		:	m_teamName{ std::move( teamName ) }
		,	m_fieldOfStudy{ std::move( fieldOfStudy ) }
		,	m_time{ std::move( time ) }
	{}

	template < typename JSON_IO >
	void
	json_io( JSON_IO & io )
	{
		io
			& json_dto::mandatory( "Team_Name", m_teamName )
			& json_dto::mandatory( "Field_of_Study", m_fieldOfStudy )
			& json_dto::mandatory( "Time", m_time );
	}

	std::string m_teamName;
	std::string m_fieldOfStudy;
    std::string m_time;
	
};

using byte_battle_t = std::vector< bytebattleTeam_t >;

namespace rr = restinio::router;
using router_t = rr::express_router_t<>;

class bytebattle_handler_t
{
public :
	explicit bytebattle_handler_t( byte_battle_t & teamInfo )
		:	m_teamInfo( teamInfo )
	{}

	bytebattle_handler_t( const bytebattle_handler_t & ) = delete;
	bytebattle_handler_t( bytebattle_handler_t && ) = delete;

	// auto on_bytebattle_list(
	// 	const restinio::request_handle_t& req, rr::route_params_t ) const
	// {
	// 	auto resp = init_resp( req->create_response() );
	// 	std::string json = json_dto::to_json(m_teamInfo);
	// 	resp.set_body(json);

	// 	return resp.done();
	// }
// auto on_weather_list(
//  		const restinio::request_handle_t& req, rr::route_params_t ) const
//  	{
//  		auto resp = init_resp( req->create_response() );
//  		std::string json = json_dto::to_json(m_teamInfo);
//  		resp.set_body(json);

//  		return resp.done();
//  	}

 auto on_new_team(
		const restinio::request_handle_t& req, rr::route_params_t )
	{
		auto resp = init_resp( req->create_response() );

 		try
		{
 			m_teamInfo.emplace_back(
			json_dto::from_json< bytebattleTeam_t >( req->body() ) );
			
		}
 		catch( const std::exception & )
		{
			mark_as_bad_request( resp );
		}
 
		return resp.done();
	} 

auto sendAllData(const restinio::request_handle_t& req, rr::route_params_t ) const
	{
		auto resp = init_resp( req->create_response() );

 		try
		{
 			std::string json = json_dto::to_json(m_teamInfo);
			resp.set_body(json);
			
		}
 		catch( const std::exception & )
		{
			mark_as_bad_request( resp );
		}
 
		return resp.done();
	} 
auto options(restinio::request_handle_t req,
restinio::router::route_params_t)
{
	const auto methods = "OPTIONS, GET, POST, PATCH, DELETE, PUT";
	auto resp = init_resp(req->create_response());
	resp.append_header(restinio::http_field::access_control_allow_methods, methods);
	resp.append_header(restinio::http_field::access_control_allow_headers, "content-type");
	resp.append_header(restinio::http_field::access_control_max_age, "86400");
	return resp.done();
}

auto send_file(const restinio::request_handle_t& req, rr::route_params_t params )
	{
		
        return req->create_response()
                 .append_header( restinio::http_field::server, "RESTinio hello world server" )
                 .append_header_date_field()
                 .append_header( restinio::http_field::content_type, "text/html; charset=utf-8" )
                 .set_body( restinio::sendfile( "index2.html" ) )
                 .done();
	}
// auto on_team_update(
// 		const restinio::request_handle_t& req, rr::route_params_t params )
// 	{
// 		const auto param_name = restinio::cast_to< std::string >( params[ "teamname" ] );
		
// 		auto resp = init_resp( req->create_response() );
		
// 		try
// 		{
// 			printf("Teamname: %s ", param_name);
	
// 			// else
// 			// {
// 			// 	mark_as_bad_request( resp );
// 			// 	resp.set_body( "No weather data #" + param_name + "\n" );
// 			// }
// 		}
// 		catch( const std::exception & /*ex*/ )
// 		{
// 			mark_as_bad_request( resp );
// 		}
		
// 		return resp.done();
// 	}
 


private :
	
	byte_battle_t & m_teamInfo;

	template < typename RESP >
	static RESP
	init_resp( RESP resp )
	{
		resp
			.append_header( "Server", "RESTinio sample server /v.0.6" )
			.append_header_date_field()
			.append_header( "Content-Type", "text/plain; charset=utf-8" );

		return resp;
	}

	template < typename RESP >
	static void
	mark_as_bad_request( RESP & resp )
	{
		resp.header().status_line( restinio::status_bad_request() );
	}
};

auto server_handler( byte_battle_t & team_collection )
{
	auto router = std::make_unique< router_t >();
	auto handler = std::make_shared< bytebattle_handler_t >( std::ref(team_collection) );

	auto by = [&]( auto method ) {
		using namespace std::placeholders;
		return std::bind( method, handler, _1, _2 );
	};

	auto method_not_allowed = []( const auto & req, auto ) {
			return req->create_response( restinio::status_method_not_allowed() )
					.connection_close()
					.done();
		};

	// Handlers for '/' path.
	//router->http_get( "/", by( &bytebattle_handler_t::send_file ) ); 
	//router->http_get( "/", by( &bytebattle_handler_t::on_bytebattle_list ) );
	
	//router->http_post( "/", by( &bytebattle_handler_t::on_new_team ) );

	//router->http_get( "/teamName/:teamName", by( &bytebattle_handler_t::on_teamName_get ) );
	router->add_handler(restinio::http_method_options(), "/", by(&bytebattle_handler_t::options)); //CORS
	router->http_get( "/index.html", by( &bytebattle_handler_t::send_file));
	router->http_post("/", by(&bytebattle_handler_t::on_new_team ));
	router->http_get( "/sendAllData", by( &bytebattle_handler_t::sendAllData)); //måske get?

	// Disable all other methods for '/'.
	// router->add_handler
	// 		restinio::router::none_of_methods(
	// 				restinio::http_method_get(), restinio::http_method_post() ),
	// 		"/", method_not_allowed );

	// // Handler for '/author/:author' path.
	//	router->http_get( "/author/:author", by( &books_handler_t::on_author_get ) );

	// // Disable all other methods for '/author/:author'.
	// router->add_handler(
	// 		restinio::router::none_of_methods( restinio::http_method_get() ),
	// 		"/author/:author", method_not_allowed );

	// Handlers for '/:booknum' path.
	// router->http_get(
	// 		R"(/:booknum(\d+))",
	// 		by( &books_handler_t::on_book_get ) );
	// router->http_put(
	// 		R"(/:booknum(\d+))",
	// 		by( &books_handler_t::on_book_update ) );
	// router->http_delete(
	// 		R"(/:booknum(\d+))",
	// 		by( &books_handler_t::on_book_delete ) );

	// Disable all other methods for '/:booknum'.
	// router->add_handler(
	// 		restinio::router::none_of_methods(
	// 				restinio::http_method_get(),
	// 				restinio::http_method_post(),
	// 				restinio::http_method_delete() ),
	// 		R"(/:booknum(\d+))", method_not_allowed );

	return router;
}

int main()
{
	
	using namespace std::chrono;

	try
	{
		using traits_t =
			restinio::traits_t<
				restinio::asio_timer_manager_t,
				restinio::single_threaded_ostream_logger_t,
				router_t >;

		byte_battle_t team_collection{
			{"CodBoyz", "SW", "25"}
		};
		
		restinio::run(
			restinio::on_this_thread< traits_t >()
				.port(8080)
				.address( "127.0.0.1" )
				.request_handler( server_handler( team_collection ) )
				.read_next_http_message_timelimit( 10s )
				.write_http_response_timelimit( 1s )
				.handle_request_timeout( 1s ) );
				
		
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
