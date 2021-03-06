#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "IEntity.h"
#include "IMovingEntity.h"
#include "SpatialHash.h"
#include "SeparatingAxisTheorem.h"
#include "CentipedeSegment.h"
#include "ObjectType.h"

#include <algorithm>
#include <vector>
#include <memory>

using std::find;
using std::copy_if;
using std::count_if;
using std::begin;
using std::end;
using std::vector;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using IMovingEntity_ptr = shared_ptr<IMovingEntity>;

/**	\class CollisionHandler
 * 	\brief A Logic Layer class that determines whether collisions have occurred
 * 	between game objects. This class makes use of the algorithm implemented in
 *  SeparatingAxisTheorem class to check for overlap between two BoundaryBox objects.
 *  Depending on which game objects are overlapping the appropriate behaviour is
 *  determined. This class aims to reduce collision checks by making use of the
 *  SpatialHash class. The spatial hash is generated every time checkCollisions()
 *  gets called. While iterating through the movable objects, the Spatial Hash is
 *  used to retrieve any nearby objects in the cell an object is located in.
 *  Collision checks are then only performed between an object and the objects in the
 *  same cell location(s).
 * 	\author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 * 	\version 3.0
 */
class CollisionHandler
{
    public:

        /** \brief Parameterized Constructor. Constructs a CollisionHandler object.
         *  \param grid is of type Grid and contains the screen width and height.
         */
        CollisionHandler(const Grid& grid);

        /** \brief Checks for collisions between the game objects that are still alive.
         *
         *  \param game_objects is a vector of shared pointers of type IEntity.
         *  \param moving_game_objects is a vector of shared pointers of type IMovingEntity.
         */
        void checkCollisions(vector<IEntity_ptr>& game_objects,
                             vector<IMovingEntity_ptr>& moving_game_objects);

        /** \brief Returns the points the player has obtained from killing game enemies.
         *  \return int
         */
        int getPointsObtained();

        /** \brief Default Destructor. Destroys a Collision Handler object.
         */
        ~CollisionHandler();
    private:
        SeparatingAxisTheorem sat_algorithm_;
        SpatialHash spatial_hash_;
        int points_obtained_;

        /**\brief Returns the number of objects of the specified object type in the
         *  range given.
         * \param game_objects_begin is a iterator to a vector of shared pointers of type IMovingEntity.
         * \param game_objects_end is a iterator to a vector of shared pointers of type IMovingEntity.
         * \param object_type is of type enum class ObjectType.
         * \return int containing the number of objects.
         */
        int countObjects(vector<IMovingEntity_ptr>::iterator game_objects_begin,
                         vector<IMovingEntity_ptr>::iterator game_objects_end,
                         ObjectType object_type);

        /**\brief Copies the objects from a vector of the specified object type in the
         *  range given to another vector.
         * \param game_objects_begin is a iterator to a vector of shared pointers of type IMovingEntity.
         * \param game_objects_end is a iterator to a vector of shared pointers of type IMovingEntity.
         * \param object_type is of type enum class ObjectType.
         * \return vector<IMovingEntity_ptr> containing the copied objects based on the object type.
         */
        vector<IMovingEntity_ptr> copyObjects(vector<IMovingEntity_ptr>::iterator game_objects_begin,
                                        vector<IMovingEntity_ptr>::iterator game_objects_end,
                                        ObjectType object_type);

        /** \brief Checks whether a PlayerBullet collides with every other game object near it.
         *  If collisions occur both call their respective eliminated()
         *  functions. Mushroom will decrement its number of lives while others will set alive status false.
         *  \param player_bullets is a vector of shared pointers to IMovingEntity objects of ObjectType::PLAYER_LASER_BULLET.
         *  \param centipede is a vector of shared pointers to IMovingEntity objects of ObjectType::CENTIPEDE.
         */
        void playerBulletCollidesWithEnemies(vector<IMovingEntity_ptr>& player_bullets,
                                             vector<IMovingEntity_ptr>& centipede);

        /** \brief Updates the centipede train after a bullet has collided with a segment.
         *  Sets the next segment as a CentipedeSegment::BodyType::HEAD and updates
         *  the collision positions of the segments following the new head.
         *  \param centipede is a vector of shared pointers to IMovingEntity objects of ObjectType::CENTIPEDE.
         *  \param segment is a shared pointer to an IEntity object of ObjectType::CENTIPEDE.
         */
        void splitCentipedeTrain(vector<IMovingEntity_ptr>& centipede,
                                 IEntity_ptr& segment);

        /** \brief Checks collisions between a centipede and a Mushroom.
         *  If a collision occurs, the Centipede segment goes down and changes direction.
         *  \param centipede is a vector of shared pointers to IMovingEntity objects of ObjectType::CENTIPEDE.
         */
        void centipedeCollidesWithMushroom(vector<IMovingEntity_ptr>& centipede);

        /** \brief Checks collisions between a centipede and a centipede.
         *  If a collision occurs, then both Centipedes go down or up and change their directions.
         *  \param centipede is a vector of shared pointers to IMovingEntity objects of ObjectType::CENTIPEDE.
         */
        void centipedeCollidesWithCentipede(vector<IMovingEntity_ptr>& centipede);

        /** \brief Updates the train behind a head that has collided with a
         *  Mushroom or another Centipede train.
         *  \param centipede is a vector of shared pointers to IMovingEntity objects of ObjectType::CENTIPEDE.
         *  \param segment is a shared pointer to an IEntity object of type ObjectType::CENTIPEDE.
         *  \param collision_point is a Position object and contains the position where a head has collided.
         *  \param poisoned_position is bool indicating whether the head collided with a poisoned mushroom.
         *  \param move_out_of_collision is a bool indicating whether the centipede train should be moved
             to get out of a collision.
         */
        void updateCentipedeTrain(vector<IMovingEntity_ptr>& centipede,
                                  IEntity_ptr segment,
                                  Position collision_point,
                                  bool poisoned_position,
                                  bool move_out_of_collision);

        /** \brief Checks collisions between a Player and other game objects.
         *  If a collision occurs, with a Mushroom the player's direction is set to NONE.
         *  If it's anything other than a Mushroom the player loses a life.
         *  \param player is a shared pointer to an IMovingEntity object of ObjectType::PLAYER.
         */
        void playerCollidesWithObjects(vector<IMovingEntity_ptr>& player);

        /** \brief Checks collisions between a Scorpion and Mushroom.
         *  If a collision occurs with a mushroom, the mushroom is set to poisoned.
         *  \param scorpions is a vector of shared pointer(s) to an IMovingEntity object of ObjectType::SCORPION.
         */
        void scorpionCollidesWithMushroom(vector<IMovingEntity_ptr>& scorpions);

        /** \brief Checks collisions between a Spider and Mushroom.
         *  If a collision occurs with a mushroom, the mushroom is set to eliminated.
         *  Its alive status becomes false.
         *  \param spiders vector of shared pointer(s) to an IMovingEntity object of ObjectType::SPIDER.
         */
        void spiderCollidesWithMushroom(vector<IMovingEntity_ptr>& spiders);
};

#endif // COLLISIONHANDLER_H
