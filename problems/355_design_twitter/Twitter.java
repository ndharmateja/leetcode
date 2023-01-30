import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Twitter {
    Map<Integer, Integer> tweetUserMap;
    Map<Integer, List<Integer>> userTweetsMap;
    Map<Integer, Set<Integer>> userFolloweesMap;
    List<Integer> tweets;

    public Twitter() {
        this.tweetUserMap = new HashMap<>();
        this.userTweetsMap = new HashMap<>();
        this.userFolloweesMap = new HashMap<>();
        this.tweets = new ArrayList<>();
    }

    public void postTweet(int userId, int tweetId) {
        this.tweetUserMap.put(tweetId, userId);
        if (!this.userTweetsMap.containsKey(userId)) {
            this.userTweetsMap.put(userId, new ArrayList<>());
        }
        this.userTweetsMap.get(userId).add(tweetId);
        this.tweets.add(tweetId);
    }

    // Improvement: If we iterate through the entire list of tweets
    // it is going to be very inefficient as we are going to go over
    // so many unrelated tweets.
    // So we get all the 'k' lists of tweets of all the users
    // the user follows along with the user themselves
    // and similar to merge 'k' sorted lists, we get the top 10 tweets
    // We would also have to store the time of the tweet along with the
    // tweet itself (counter variable can be used)
    // And the whole list of tweets wouldn't be needed
    // And also the tweetUserMap wouldn't be needed
    // Reference: https://www.youtube.com/watch?v=pNichitDD2E
    public List<Integer> getNewsFeed(int userId) {
        List<Integer> feed = new ArrayList<>();
        for (int i = tweets.size() - 1; i >= 0; i--) {
            int tweetId = this.tweets.get(i);
            int tweetUserId = this.tweetUserMap.get(tweetId);
            if (tweetUserId == userId
                    || this.userFolloweesMap.getOrDefault(userId, new HashSet<>()).contains(tweetUserId)) {
                feed.add(tweetId);
                if (feed.size() == 10)
                    break;
            }
        }
        return feed;
    }

    public void follow(int followerId, int followeeId) {
        if (!this.userFolloweesMap.containsKey(followerId)) {
            this.userFolloweesMap.put(followerId, new HashSet<>());
        }
        this.userFolloweesMap.get(followerId).add(followeeId);
    }

    public void unfollow(int followerId, int followeeId) {
        if (this.userFolloweesMap.containsKey(followerId)) {
            this.userFolloweesMap.get(followerId).remove(followeeId);
        }
    }
}