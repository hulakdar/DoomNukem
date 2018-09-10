#include "dn_rendering.h"
#include "dn_simple_drawing.h"
#include "dn_events.h"
#include "dn_io.h"
#include "dn.h"

static inline void vsync( t_game_state *game_state )
{
	const current_ticks = SDL_GetTicks( );
	const frame_time = current_ticks - game_state->last_time;

	if ( frame_time < 16 )
		WAIT( 16 - frame_time );
	game_state->last_time = current_ticks;
	game_state->frame_time = frame_time;
}

int init_render_state( t_render_state *renderer )
{
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 ||
		!( renderer->window = SDL_CreateWindow( "RT",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer->w,
			renderer->h, SDL_WINDOW_FLAGS ) ) )
	{
		char message[ ] = "failed to initialize SDL";
		DN_ERROR( message );
		return ( 1 );
	}
	return ( 0 );
}

void init_renderer( t_render_state *render_state )
{
	render_state->renderer =
		SDL_CreateRenderer( render_state->window, -1, SDL_RENDERER_ACCELERATED );
	//SDL_RenderSetLogicalSize(render_state->renderer, render_state->w, render_state->h);
	render_state->pixels = ft_memalloc( sizeof( int ) * ( render_state->w * render_state->h ) );
	render_state->back_buffer = SDL_CreateTexture( render_state->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, render_state->w, render_state->h );
}

void draw_wall( struct s_game_state *game_state, t_screen_wall* screen_wall_list )
{

}

void draw_bunch( struct s_game_state *game_state, t_bunch* bunch )
{
	t_screen_wall* current_wall = bunch->screen_walls_list;
	do
	{
		draw_wall( game_state, current_wall );
	} while ( ( current_wall = current_wall->next ) );
}

void draw_frame( struct s_game_state *game_state )
{
	t_bunch* current_bunch = game_state->bunches;
	do
	{
		draw_bunch( game_state, current_bunch );
	} while ( (current_bunch = current_bunch->next) );
}

void	draw_loop( struct s_game_state *game_state )
{
	init_renderer( &game_state->render_state );
	while ( true )
	{
		ft_memset( game_state->upper_empty_pixels, 0, W * sizeof( short ) );
		ft_memset( game_state->lower_empty_pixels, 0, W * sizeof( short ) );

		game_state->player.sector = update_sector( game_state, game_state->player.position.x, game_state->player.sector );

		analize_sector( game_state, game_state->player.sector, false );

		sort_bunches( game_state->bunches );

		draw_frame( game_state );

		SDL_UpdateTexture( game_state->render_state.back_buffer, NULL, game_state->render_state.pixels, game_state->render_state.w * 4 );
		SDL_RenderCopy( game_state->render_state.renderer, game_state->render_state.back_buffer, NULL, NULL );
		SDL_RenderPresent( game_state->render_state.renderer );
		vsync( game_state );

		free_bunch_list_by_head( game_state->bunches );
		game_state->bunches = NULL;
	}
}