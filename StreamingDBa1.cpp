#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
    movies = new MoviesTree();
    moviesSortedByRating = new GenreMoviesTree();
    comedy = new GenreMoviesTree();
    drama = new GenreMoviesTree();
    action = new GenreMoviesTree();
    fantasy = new GenreMoviesTree();
    users = new UsersTree();
    groups = new GroupsTree();
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    delete movies;
    delete moviesSortedByRating;
    delete comedy;
    delete drama;
    delete action;
    delete fantasy;
    delete users;
    delete groups;


    // TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    try{
        Movie * movie = new Movie(movieId,vipOnly,views,genre);
        movies->add(movie);
        getGenreTree(movie)->add(movie);
        moviesSortedByRating->add(movie);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    try{
        Movie * movie = movies->getData(movieId);
        moviesSortedByRating->remove(movie);
        getGenreTree(movie)->remove(movie);
        movies->remove(movieId);

    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    try{
        User * user = new User(userId,isVip);
        users->add(user);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }

    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;

}

StatusType streaming_database::remove_user(int userId)
{
    try{
        User* user = users->getData(userId);
        if(user->getGroupId() != 0)
        {
           user->getGroup()->remove(userId);
           users->remove(userId);
        }

    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    try{
        Group * group = new Group(groupId);
        groups->add(group);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;



}

StatusType streaming_database::remove_group(int groupId)
{
    try{
        Group* group = groups->getData(groupId);
        group->clearGroup(group->getHead());
        groups->remove(groupId);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch(NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    try{
        Group * group = groups->getData(groupId);
        User* user = users->getData(userId);
        group->add(user);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
        return StatusType::INVALID_INPUT;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }

    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;

}

StatusType streaming_database::user_watch(int userId, int movieId)
{

    try{
        User* user = users->getData(userId);
        Movie* movie = movies->getData(movieId);
        moviesSortedByRating->remove(movie);
        getGenreTree(movie->getGenre())->remove(movie);
        user->watch(movie);
        moviesSortedByRating->add(movie);
        getGenreTree(movie->getGenre())->add(movie);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
        return StatusType::INVALID_INPUT;
    }


    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }
    catch (NotVip){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    try{
        Group * group = groups->getData(groupId);
        Movie* movie = movies->getData(movieId);

        moviesSortedByRating->remove(movie);
        getGenreTree(movie->getGenre())->remove(movie);
        group->watch(movie);
        moviesSortedByRating->add(movie);
        getGenreTree(movie->getGenre())->add(movie);
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
        return StatusType::INVALID_INPUT;
    }

    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    try{
        return getGenreTree(genre)->getSize();
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
        return StatusType::INVALID_INPUT;
    }

    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{

    if(output == NULL)
        return StatusType::FAILURE;
    try
    {
        getGenreTree(genre)->putDataInOrder(output);

        // TODO: Your code goes here
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    catch(EmptyTree){
        return StatusType::FAILURE;
    }

    catch(...){
        return StatusType::FAILURE;
    }
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    try
    {
        int res =  users->getData(userId)->getViews(genreToInt(genre));
        return res;
    }


    catch (std::bad_alloc)
            {
                    return StatusType::ALLOCATION_ERROR;
            }

    catch (NotValidId){
            return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
            return StatusType::INVALID_INPUT;
    }


    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{

    try{
        User * user = users->getData(userId);
        Movie* movie = movies->getData(movieId);
        moviesSortedByRating->remove(movie);
        getGenreTree(movie->getGenre())->remove(movie);
        user->rate(movie,rating);
        moviesSortedByRating->add(movie);
        getGenreTree(movie->getGenre())->add(movie);
    }



    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NotVip){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
        return StatusType::INVALID_INPUT;
    }

    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }
    catch(NoNodeExist)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
try{
     GenreMoviesTree* genre_tree = getGenreTree(groups->getData(groupId)->getMostViewedGenre());
     if(genre_tree->getSize() <= 0)
         return StatusType::FAILURE;
    return genre_tree->getHighest()->getId();
    }
    catch (std::bad_alloc)
            {
                    return StatusType::ALLOCATION_ERROR;
            }

    catch (NotVip){
            return StatusType::FAILURE;
    }

    catch (NotValidId){
            return StatusType::INVALID_INPUT;
    }

    catch (NotValidInput){
            return StatusType::INVALID_INPUT;
    }

    catch(alreadyExists)
            {
                    return StatusType::FAILURE;
            }
    catch(NoNodeExist)
            {
                    return StatusType::FAILURE;
            }
}


